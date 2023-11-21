// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2017 MediaTek Inc.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/kthread.h>
#include <linux/atomic.h>
#include <linux/mutex.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/sched/rt.h>
#include <linux/platform_device.h>
#include <linux/suspend.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#include <mtk_pbm.h>
#include <mtk_pbm_common.h>
#include <mtk_pbm_data.h>
#include <linux/power_supply.h>

#ifndef DISABLE_PBM_FEATURE
#include <linux/iio/consumer.h>
#include <mtk_gpufreq.h>
#if (defined(CONFIG_MACH_MT6877) \
	|| defined(CONFIG_MACH_MT6768) \
	|| defined(CONFIG_MACH_MT6781) \
	|| defined(CONFIG_MACH_MT6833))
//#include <mach/upmu_sw.h>
//#include <mt-plat/upmu_common.h>
#include <mt-plat/mtk_auxadc_intf.h>
#include <mtk_cpufreq_api.h>
#ifdef CONFIG_THERMAL
#include <mach/mtk_thermal.h>
#endif
#endif
#include <mtk_ppm_api.h>
#include <mtk_dynamic_loading_throttling.h>
#endif

#ifndef DISABLE_PBM_FEATURE
static bool mt_pbm_debug;
static int g_pbm_stop;

static int mt_pbm_log_divisor;
static int mt_pbm_log_counter;




#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "[PBM] " fmt

#define BIT_CHECK(a, b) ((a) & (1<<(b)))

static struct hpf hpf_ctrl = {
	.switch_md1 = 1,
	.switch_gpu = 0,
	.switch_flash = 0,

	.cpu_volt = 1000,	/* 1V = boot up voltage */
	.gpu_volt = 0,
	.cpu_num = 1,		/* default cpu0 core */

	.loading_leakage = 0,
	.loading_dlpt = 0,
	.loading_md1 = 0,
	.loading_cpu = 0,
	.loading_gpu = 0,
	.loading_flash = MAX_FLASH_POWER,	/* fixed */
	.to_cpu_budget = 0,
	.to_gpu_budget = 0,
};

static struct hpf hpf_ctrl_manual = {
	.loading_leakage = 0,
	.loading_dlpt = 0,
	.loading_md1 = 0,
	.loading_cpu = 0,
	.loading_gpu = 0,
	.loading_flash = 0,
	.to_cpu_budget = 0,
	.to_gpu_budget = 0,
};

static struct pbm pbm_ctrl = {
	/* feature key */
	.feature_en = 1,
	.pbm_drv_done = 0,
	.hpf_en = 63,/* bin: 111111 (Flash, GPU, CPU, MD3, MD1, DLPT) */
	.manual_mode = 0, /*normal=0, UT(throttle)=1, UT(NO throttle)=2 */
};

int g_dlpt_need_do = 1;
static DEFINE_MUTEX(pbm_mutex);
static DEFINE_MUTEX(pbm_table_lock);
static struct task_struct *pbm_thread;
static atomic_t kthread_nreq = ATOMIC_INIT(0);
/* extern u32 get_devinfo_with_index(u32 index); */

/*
 * weak function
 */
int __attribute__ ((weak))
tscpu_get_min_cpu_pwr(void)
{
	pr_warn_ratelimited("%s not ready\n", __func__);
	return 0;
}

unsigned int __attribute__ ((weak))
mt_ppm_get_leakage_mw(enum ppm_cluster_lkg cluster)
{
	pr_notice_ratelimited("%s not ready\n", __func__);
	return 0;
}

unsigned int __attribute__ ((weak))
mt_gpufreq_get_leakage_mw(void)
{
	pr_warn_ratelimited("%s not ready\n", __func__);
	return 0;
}

void __attribute__ ((weak))
mt_ppm_dlpt_set_limit_by_pbm(unsigned int limited_power)
{
	pr_warn_ratelimited("%s not ready\n", __func__);
}

void __attribute__ ((weak))
mt_gpufreq_set_power_limit_by_pbm(unsigned int limited_power)
{
	pr_warn_ratelimited("%s not ready\n", __func__);
}

#if (defined(CONFIG_MACH_MT6877) \
	|| defined(CONFIG_MACH_MT6768) \
	|| defined(CONFIG_MACH_MT6781) \
	|| defined(CONFIG_MACH_MT6833))
u32 __attribute__ ((weak))
spm_vcorefs_get_MD_status(void)
{
	pr_notice("%s not ready\n", __func__);
	return 0;
}

static int get_battery_volt(void)
{
	return pmic_get_auxadc_value(AUXADC_LIST_BATADC);
	/* return 3900; */
}


#else
static int get_battery_volt(void)
{
	union power_supply_propval prop;
	struct power_supply *psy;
	int ret;

	psy = power_supply_get_by_name("battery");
	if (psy == NULL) {
		pr_notice("%s can't get battery node\n", __func__);
		return -ENODEV;
	}

	ret = power_supply_get_property(psy,
		POWER_SUPPLY_PROP_VOLTAGE_NOW, &prop);
	if (ret || prop.intval < 0) {
		pr_info("%s: POWER_SUPPLY_PROP_VOLTAGE_NOW fail\n", __func__);
		return -EINVAL;
	}
#ifdef OPLUS_FEATURE_CHG_BASIC
	return prop.intval;
#else
	return prop.intval/1000;
#endif
}
#endif
unsigned int ma_to_mw(unsigned int val)
{
	unsigned int bat_vol = 0;
	unsigned int ret_val = 0;

	bat_vol = get_battery_volt();	/* return mV */
	if (bat_vol <= 0) {
		pr_notice_ratelimited("[%s] wrong volt=%d, set 4V\n",
			bat_vol);
		bat_vol = 4000;
	}

	ret_val = (bat_vol * val) / 1000;	/* mW = (mV * mA)/1000 */
	pr_info("[%s] %d(mV) * %d(mA) = %d(mW)\n",
		__func__, bat_vol, val, ret_val);

	return ret_val;
}

void dump_kicker_info(void)
{
	struct hpf *hpfmgr = &hpf_ctrl;

	if (mt_pbm_debug)
		pr_info("(M1/F/G)=%d,%d,%d;(C/G)=%ld,%ld\n",
			hpfmgr->switch_md1, hpfmgr->switch_flash,
			hpfmgr->switch_gpu, hpfmgr->loading_cpu,
			hpfmgr->loading_gpu);
}

int hpf_get_power_leakage(void)
{
	struct hpf *hpfmgr = &hpf_ctrl;
	unsigned int leakage_cpu = 0, leakage_gpu = 0;

	leakage_cpu = mt_ppm_get_leakage_mw(TOTAL_CLUSTER_LKG);
	leakage_gpu = mt_gpufreq_get_leakage_mw();
	hpfmgr->loading_leakage = leakage_cpu + leakage_gpu;

	if (mt_pbm_debug)
		pr_info("[%s] %ld=%d+%d\n", __func__,
			hpfmgr->loading_leakage, leakage_cpu, leakage_gpu);

	return hpfmgr->loading_leakage;
}

unsigned long hpf_get_power_cpu(void)
{
	struct hpf *hpfmgr = &hpf_ctrl;

	return hpfmgr->loading_cpu;
}

unsigned long hpf_get_power_gpu(void)
{
	struct hpf *hpfmgr = &hpf_ctrl;

	if (hpfmgr->switch_gpu)
		return hpfmgr->loading_gpu;
	else
		return 0;
}

unsigned long hpf_get_power_flash(void)
{
	struct hpf *hpfmgr = &hpf_ctrl;

	if (hpfmgr->switch_flash)
		return hpfmgr->loading_flash;
	else
		return 0;
}

unsigned long hpf_get_power_dlpt(void)
{
	struct hpf *hpfmgr = &hpf_ctrl;

	return hpfmgr->loading_dlpt;
}

unsigned long hpf_get_power_md1(void)
{
	struct hpf *hpfmgr = &hpf_ctrl;

	if (hpfmgr->switch_md1)
		hpfmgr->loading_md1 = get_md1_power(MAX_POWER, true);
	else
		hpfmgr->loading_md1 = 0;

	return hpfmgr->loading_md1;
}

static void pbm_allocate_budget_manager(void)
{
	int _dlpt = 0, leakage = 0, md1 = 0, dlpt = 0;
	int cpu = 0, gpu = 0, flash = 0, tocpu = 0, togpu = 0;
	int multiple = 0;
	int cpu_lower_bound = tscpu_get_min_cpu_pwr();
	static int pre_tocpu, pre_togpu;

	if (pbm_ctrl.manual_mode == 1 || pbm_ctrl.manual_mode == 2) {
		leakage = hpf_ctrl_manual.loading_leakage;
		dlpt = hpf_ctrl_manual.loading_dlpt;
		md1 = hpf_ctrl_manual.loading_md1;
		cpu = hpf_ctrl_manual.loading_cpu;
		gpu = hpf_ctrl_manual.loading_gpu;
		flash = hpf_ctrl_manual.loading_flash;

	} else {
		mutex_lock(&pbm_table_lock);
		/* dump_kicker_info(); */
		leakage = hpf_get_power_leakage();
		md1 = hpf_get_power_md1();
		dlpt = hpf_get_power_dlpt();
		cpu = hpf_get_power_cpu();
		gpu = hpf_get_power_gpu();
		flash = hpf_get_power_flash();
		mutex_unlock(&pbm_table_lock);
	}

	if (mt_pbm_log_divisor) {
		mt_pbm_log_counter = (mt_pbm_log_counter + 1) %
			mt_pbm_log_divisor;

		if (mt_pbm_log_counter == 1)
			mt_pbm_debug = 1;
		else
			mt_pbm_debug = 0;
	}

	/* no any resource can allocate */
	if (dlpt == 0) {
		if (mt_pbm_debug)
			pr_info("DLPT=0\n");

		return;
	}

	_dlpt = dlpt - (leakage + md1 + flash);
	if (_dlpt < 0)
		_dlpt = 0;

	/* if gpu no need resource, so all allocate to cpu */
	if (gpu == 0) {
		tocpu = _dlpt;

		/* check CPU lower bound */
		if (tocpu < cpu_lower_bound)
			tocpu = cpu_lower_bound;

		if (tocpu <= 0)
			tocpu = 1;

		if (pbm_ctrl.manual_mode != 2)
			mt_ppm_dlpt_set_limit_by_pbm(tocpu);
	} else {
		multiple = (_dlpt * 1000) / (cpu + gpu);

		if (multiple > 0) {
			tocpu = (multiple * cpu) / 1000;
			togpu = (multiple * gpu) / 1000;
		} else {
			tocpu = 1;
			togpu = 1;
		}

		/* check CPU lower bound */
		if (tocpu < cpu_lower_bound) {
			tocpu = cpu_lower_bound;
			togpu = _dlpt - cpu_lower_bound;
		}

		if (tocpu <= 0)
			tocpu = 1;
		if (togpu <= 0)
			togpu = 1;

		if (pbm_ctrl.manual_mode != 2) {
			mt_ppm_dlpt_set_limit_by_pbm(tocpu);
			mt_gpufreq_set_power_limit_by_pbm(togpu);
		}
	}

	hpf_ctrl.to_cpu_budget = tocpu;
	hpf_ctrl.to_gpu_budget = togpu;

	if (mt_pbm_debug) {
		pr_info("(C/G)=%d,%d=>(D/L/M1/F/C/G)=%d,%d,%d,%d,%d,%d(Multi:%d),%d\n",
			cpu, gpu, dlpt, leakage, md1, flash, tocpu, togpu,
			multiple, cpu_lower_bound);
	} else {
	#if (defined(CONFIG_MACH_MT6877) \
	|| defined(CONFIG_MACH_MT6768) \
	|| defined(CONFIG_MACH_MT6781) \
	|| defined(CONFIG_MACH_MT6833))
		if (((abs(pre_tocpu - tocpu) >= 100) && cpu > tocpu) ||
			((abs(pre_togpu - togpu) >= 30) && gpu > togpu)) {
	#else
		if (((abs(pre_tocpu - tocpu) >= 10) && cpu > tocpu) ||
			((abs(pre_togpu - togpu) >= 10) && gpu > togpu)) {
	#endif
			pr_info_ratelimited
			("(C/G)=%d,%d=>(D/L/M1/F/C/G)=%d,%d,%d,%d,%d,%d(Multi:%d),%d\n",
				cpu, gpu, dlpt, leakage, md1, flash, tocpu, togpu,
				multiple, cpu_lower_bound);
			pre_tocpu = tocpu;
			pre_togpu = togpu;
		} else if ((cpu > tocpu) || (gpu > togpu)) {
			pr_warn_ratelimited
				("(C/G)=%d,%d => (D/L/M1/F/C/G)=%d,%d,%d,%d,%d,%d (Multi:%d),%d\n",
				cpu, gpu, dlpt, leakage, md1, flash, tocpu, togpu,
				multiple, cpu_lower_bound);
		} else {
			pre_tocpu = tocpu;
			pre_togpu = togpu;
		}
	}

}

static bool pbm_func_enable_check(void)
{
	struct pbm *pwrctrl = &pbm_ctrl;

	if (!pwrctrl->feature_en || !pwrctrl->pbm_drv_done) {
		pr_info("feature_en: %d, pbm_drv_done: %d\n",
		pwrctrl->feature_en, pwrctrl->pbm_drv_done);
		return false;
	}

	return true;
}

static bool pbm_update_table_info(enum pbm_kicker kicker, struct mrp *mrpmgr)
{
	struct hpf *hpfmgr = &hpf_ctrl;
	bool is_update = false;

	switch (kicker) {
	case KR_DLPT:		/* kicker 0 */
		if (hpfmgr->loading_dlpt != mrpmgr->loading_dlpt) {
			hpfmgr->loading_dlpt = mrpmgr->loading_dlpt;
			is_update = true;
		}
		break;
	case KR_MD1:		/* kicker 1 */
		if (hpfmgr->switch_md1 != mrpmgr->switch_md) {
			hpfmgr->switch_md1 = mrpmgr->switch_md;
			is_update = true;
		}
		break;
	case KR_MD3:		/* kicker 2 */
		pr_warn("should not kicker KR_MD3\n");
		break;
	case KR_CPU:		/* kicker 3 */
		hpfmgr->cpu_volt = mrpmgr->cpu_volt;
		if (hpfmgr->loading_cpu != mrpmgr->loading_cpu
		    || hpfmgr->cpu_num != mrpmgr->cpu_num) {
			hpfmgr->loading_cpu = mrpmgr->loading_cpu;
			hpfmgr->cpu_num = mrpmgr->cpu_num;
			is_update = true;
		}
		break;
	case KR_GPU:		/* kicker 4 */
		hpfmgr->gpu_volt = mrpmgr->gpu_volt;
		if (hpfmgr->switch_gpu != mrpmgr->switch_gpu
		    || hpfmgr->loading_gpu != mrpmgr->loading_gpu) {
			hpfmgr->switch_gpu = mrpmgr->switch_gpu;
			hpfmgr->loading_gpu = mrpmgr->loading_gpu;
			is_update = true;
		}
		break;
	case KR_FLASH:		/* kicker 5 */
		if (hpfmgr->switch_flash != mrpmgr->switch_flash) {
			hpfmgr->switch_flash = mrpmgr->switch_flash;
			is_update = true;
		}
		break;
	default:
		pr_warn("[%s] ERROR, unknown kicker [%d]\n", __func__, kicker);
		WARN_ON_ONCE(1);
		break;
	}

	return is_update;
}

static void pbm_wake_up_thread(enum pbm_kicker kicker, struct mrp *mrpmgr)
{
	if (atomic_read(&kthread_nreq) <= 0) {
		atomic_inc(&kthread_nreq);
		wake_up_process(pbm_thread);
	}

	while (kicker == KR_FLASH && mrpmgr->switch_flash == 1) {
		if (atomic_read(&kthread_nreq) == 0)
			return;
	}
}

static void mtk_power_budget_manager(enum pbm_kicker kicker, struct mrp *mrpmgr)
{
	bool pbm_enable = false;
	bool pbm_update = false;

	mutex_lock(&pbm_table_lock);
	pbm_update = pbm_update_table_info(kicker, mrpmgr);
	mutex_unlock(&pbm_table_lock);
	if (!pbm_update)
		return;

	pbm_enable = pbm_func_enable_check();
	if (!pbm_enable)
		return;

	pbm_wake_up_thread(kicker, mrpmgr);
}

/*
 * kicker: 0
 * who call : PMIC
 * i_max: mA
 * condition: persentage decrease 1%, then update i_max
 */
void kicker_pbm_by_dlpt(int i_max)
{
	struct pbm *pwrctrl = &pbm_ctrl;
	struct mrp mrpmgr = {0};

	mrpmgr.loading_dlpt = ma_to_mw(i_max);

	if (BIT_CHECK(pwrctrl->hpf_en, KR_DLPT))
		mtk_power_budget_manager(KR_DLPT, &mrpmgr);
}

/*
 * kicker: 1, 2
 * who call : MD1
 * condition: on/off
 */
void kicker_pbm_by_md(enum pbm_kicker kicker, bool status)
{
	struct pbm *pwrctrl = &pbm_ctrl;
	struct mrp mrpmgr = {0};

	mrpmgr.switch_md = status;

	if (BIT_CHECK(pwrctrl->hpf_en, kicker))
		mtk_power_budget_manager(kicker, &mrpmgr);
}

/*
 * kicker: 3
 * who call : CPU
 * loading: mW
 * condition: opp changed
 */
void kicker_pbm_by_cpu(unsigned int loading, int core, int voltage)
{
	struct pbm *pwrctrl = &pbm_ctrl;
	struct mrp mrpmgr = {0};

	mrpmgr.loading_cpu = loading;
	mrpmgr.cpu_num = core;
	mrpmgr.cpu_volt = voltage;

	if (BIT_CHECK(pwrctrl->hpf_en, KR_CPU))
		mtk_power_budget_manager(KR_CPU, &mrpmgr);
}

/*
 * kicker: 4
 * who call : GPU
 * loading: mW
 * condition: opp changed
 */
void kicker_pbm_by_gpu(bool status, unsigned int loading, int voltage)
{
	struct pbm *pwrctrl = &pbm_ctrl;
	struct mrp mrpmgr = {0};

	mrpmgr.switch_gpu = status;
	mrpmgr.loading_gpu = loading;
	mrpmgr.gpu_volt = voltage;

	if (BIT_CHECK(pwrctrl->hpf_en, KR_GPU))
		mtk_power_budget_manager(KR_GPU, &mrpmgr);
}

/*
 * kicker: 5
 * who call : Flash
 * condition: on/off
 */
void kicker_pbm_by_flash(bool status)
{
	struct pbm *pwrctrl = &pbm_ctrl;
	struct mrp mrpmgr = {0};

	mrpmgr.switch_flash = status;

	if (BIT_CHECK(pwrctrl->hpf_en, KR_FLASH))
		mtk_power_budget_manager(KR_FLASH, &mrpmgr);
}

static int pbm_thread_handle(void *data)
{
	int g_dlpt_state_sync = 0;

	while (1) {

		set_current_state(TASK_INTERRUPTIBLE);

		if (kthread_should_stop())
			break;

		if (atomic_read(&kthread_nreq) <= 0) {
			schedule();
			continue;
		}

		set_current_state(TASK_RUNNING);

		mutex_lock(&pbm_mutex);
		if (g_dlpt_need_do == 1) {
			if (g_pbm_stop == 0) {
				pbm_allocate_budget_manager();
				g_dlpt_state_sync = 0;
			} else {
				pr_notice("DISABLE PBM\n");

				if (g_dlpt_state_sync == 0) {
					mt_ppm_dlpt_set_limit_by_pbm(0);
					mt_gpufreq_set_power_limit_by_pbm(0);
					g_dlpt_state_sync = 1;
					pr_info("Release DLPT limit\n");
				}
			}
		}
		atomic_dec(&kthread_nreq);
		mutex_unlock(&pbm_mutex);
	}

	return 0;
}

static int create_pbm_kthread(void)
{
	struct pbm *pwrctrl = &pbm_ctrl;

	pbm_thread = kthread_create(pbm_thread_handle, (void *)NULL, "pbm");
	if (IS_ERR(pbm_thread))
		return PTR_ERR(pbm_thread);

	wake_up_process(pbm_thread);
	pwrctrl->pbm_drv_done = 1;
	/* avoid other hpf call thread before thread init done */

	return 0;
}

static int
_mt_pbm_pm_callback(struct notifier_block *nb,
		unsigned long action, void *ptr)
{
	switch (action) {

	case PM_SUSPEND_PREPARE:
		if (mt_pbm_debug)
			pr_info("PM_SUSPEND_PREPARE:start\n");

		mutex_lock(&pbm_mutex);
		g_dlpt_need_do = 0;
		mutex_unlock(&pbm_mutex);
		if (mt_pbm_debug)
			pr_info("PM_SUSPEND_PREPARE:end\n");

		break;

	case PM_HIBERNATION_PREPARE:
		break;

	case PM_POST_SUSPEND:
		if (mt_pbm_debug)
			pr_info("PM_POST_SUSPEND:start\n");

		mutex_lock(&pbm_mutex);
		g_dlpt_need_do = 1;
		mutex_unlock(&pbm_mutex);
		if (mt_pbm_debug)
			pr_info("PM_POST_SUSPEND:end\n");

		break;

	case PM_POST_HIBERNATION:
		break;

	default:
		return NOTIFY_DONE;
	}
	return NOTIFY_OK;
}

/* CONFIG_PBM_PROC_FS */
/*
 * show current debug status
 */
static int mt_pbm_debug_proc_show(struct seq_file *m, void *v)
{
	if (mt_pbm_debug)
		seq_puts(m, "pbm debug enabled\n");
	else
		seq_puts(m, "pbm debug disabled\n");

	seq_printf(m, "manual_mode: %d\n", pbm_ctrl.manual_mode);
	if (pbm_ctrl.manual_mode > 0) {
		seq_printf(m, "request (C/G)=%lu,%lu=>(D/L/M1/F)=%lu,%lu,%lu,%lu\n",
			hpf_ctrl_manual.loading_cpu,
			hpf_ctrl_manual.loading_gpu,
			hpf_ctrl_manual.loading_dlpt,
			hpf_ctrl_manual.loading_leakage,
			hpf_ctrl_manual.loading_md1,
			hpf_ctrl_manual.loading_flash);
	} else {
		seq_printf(m, "request (C/G)=%lu,%lu=>(D/L/M1/F)=%lu,%lu,%lu,%lu\n",
			hpf_ctrl.loading_cpu,
			hpf_ctrl.loading_gpu,
			hpf_ctrl.loading_dlpt,
			hpf_ctrl.loading_leakage,
			hpf_ctrl.loading_md1,
			hpf_ctrl.loading_flash);
	}
	seq_printf(m, "budget (C/G)=%lu,%lu\n",
		hpf_ctrl.to_cpu_budget,
		hpf_ctrl.to_gpu_budget);

	return 0;
}

/*
 * enable debug message
 */
static ssize_t mt_pbm_debug_proc_write
(struct file *file, const char __user *buffer, size_t count, loff_t *data)
{
	char desc[32];
	int len = 0;
	int debug = 0;

	len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
	if (copy_from_user(desc, buffer, len))
		return 0;
	desc[len] = '\0';

	/* if (sscanf(desc, "%d", &debug) == 1) { */
	if (kstrtoint(desc, 10, &debug) == 0) {
		if (debug == 0)
			mt_pbm_debug = 0;
		else if (debug == 1)
			mt_pbm_debug = 1;
		else
			pr_notice("should be [0:disable,1:enable]\n");
	} else
		pr_notice("should be [0:disable,1:enable]\n");

	return count;
}
#if (defined(CONFIG_MACH_MT6877) \
	|| defined(CONFIG_MACH_MT6768) \
	|| defined(CONFIG_MACH_MT6781) \
	|| defined(CONFIG_MACH_MT6833))
static int mt_pbm_debug_log_reduc_proc_show(struct seq_file *m, void *v)
{
	if (mt_pbm_log_divisor) {
		seq_puts(m, "pbm debug enabled\n");
		seq_printf(m, "The divisor number is :%d\n",
			mt_pbm_log_divisor);
	} else {
		seq_puts(m, "Log reduction disabled\n");
	}

	return 0;
}

static ssize_t mt_pbm_debug_log_reduc_proc_write
(struct file *file, const char __user *buffer, size_t count, loff_t *data)
{
	char desc[32];
	int len = 0;
	int debug = 0;

	len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
	if (copy_from_user(desc, buffer, len))
		return 0;
	desc[len] = '\0';

	/* if (sscanf(desc, "%d", &debug) == 1) { */
	if (kstrtoint(desc, 10, &debug) == 0) {
		if (debug == 0) {
			mt_pbm_log_divisor = 0;
			mt_pbm_debug = 0;
		} else if (debug > 0) {
			mt_pbm_log_divisor = debug;
			mt_pbm_debug = 1;
			mt_pbm_log_counter = 0;
		} else {
			pr_notice("Should be >=0 [0:disable,other:enable]\n");
		}
	} else
		pr_notice("Should be >=0 [0:disable,other:enable]\n");

	return count;
}


#endif



static int mt_pbm_stop_proc_show(struct seq_file *m, void *v)
{
	if (g_pbm_stop)
		seq_puts(m, "pbm stop\n");
	else
		seq_puts(m, "pbm enable\n");

	return 0;
}

static ssize_t mt_pbm_stop_proc_write
(struct file *file, const char __user *buffer, size_t count, loff_t *data)
{
	char desc[32];
	int len = 0;
	int debug = 0;

	len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
	if (copy_from_user(desc, buffer, len))
		return 0;
	desc[len] = '\0';

	/* if (sscanf(desc, "%d", &debug) == 1) { */
	if (kstrtoint(desc, 10, &debug) == 0) {
		g_pbm_stop = debug;
		if (debug == 0)
			g_pbm_stop = 0;

		else if (debug == 1)

			g_pbm_stop = 1;

		else
			pr_notice("Should be [0:enable pbm, 1:stop pbm]\n");
	} else
		pr_notice("Should be [0:enable pbm, 1:stop pbm]\n");

	return count;
}

static int mt_pbm_manual_mode_proc_show(struct seq_file *m, void *v)
{
	if (pbm_ctrl.manual_mode >= 1)
		seq_puts(m, "pbm manual mode enabled\n");
	else
		seq_puts(m, "pbm manual disabled\n");

	seq_puts(m, "pbm manual disabled\n");

	return 0;
}

static ssize_t mt_pbm_manual_mode_proc_write
(struct file *file, const char __user *buffer, size_t count, loff_t *data)
{
	char desc[64];
	int len = 0, manual_mode = 0;
	int loading_leakage, loading_dlpt, loading_md1;
	int loading_cpu, loading_gpu, loading_flash;

	len = (count < (sizeof(desc) - 1)) ? count : (sizeof(desc) - 1);
	if (copy_from_user(desc, buffer, len))
		return 0;
	desc[len] = '\0';

	if (sscanf(desc, "%d %d %d %d %d %d %d", &manual_mode, &loading_dlpt,
		&loading_leakage, &loading_md1, &loading_cpu, &loading_gpu,
		&loading_flash) != 7) {
		pr_notice("parameter number not correct\n");
		return -EPERM;
	}

	if (manual_mode == 1 || manual_mode == 2) {
		hpf_ctrl_manual.loading_leakage = loading_leakage;
		hpf_ctrl_manual.loading_dlpt = loading_dlpt;
		hpf_ctrl_manual.loading_md1 = loading_md1;
		hpf_ctrl_manual.loading_cpu = loading_cpu;
		hpf_ctrl_manual.loading_gpu = loading_gpu;
		hpf_ctrl_manual.loading_flash = loading_flash;
		pbm_ctrl.manual_mode = manual_mode;
		pbm_allocate_budget_manager();
	} else if (manual_mode == 0)
		pbm_ctrl.manual_mode = 0;
	else
		pr_notice("pbm manual setting should be 0 or 1 or 2\n");

	return count;
}

#define PROC_FOPS_RW(name)						\
static int mt_ ## name ## _proc_open(struct inode *inode, struct file *file)\
{									\
	return single_open(file, mt_ ## name ## _proc_show, PDE_DATA(inode));\
}									\
static const struct file_operations mt_ ## name ## _proc_fops = {	\
	.owner		= THIS_MODULE,					\
	.open		= mt_ ## name ## _proc_open,			\
	.read		= seq_read,					\
	.llseek		= seq_lseek,					\
	.release	= single_release,				\
	.write		= mt_ ## name ## _proc_write,			\
}

#define PROC_FOPS_RO(name)						\
static int mt_ ## name ## _proc_open(struct inode *inode, struct file *file)\
{									\
	return single_open(file, mt_ ## name ## _proc_show, PDE_DATA(inode));\
}									\
static const struct file_operations mt_ ## name ## _proc_fops = {	\
	.owner		= THIS_MODULE,				\
	.open		= mt_ ## name ## _proc_open,		\
	.read		= seq_read,				\
	.llseek		= seq_lseek,				\
	.release	= single_release,			\
}

#define PROC_ENTRY(name)	{__stringify(name), &mt_ ## name ## _proc_fops}

PROC_FOPS_RW(pbm_debug);

PROC_FOPS_RW(pbm_stop);
#if (defined(CONFIG_MACH_MT6877) \
	|| defined(CONFIG_MACH_MT6768) \
	|| defined(CONFIG_MACH_MT6781) \
	|| defined(CONFIG_MACH_MT6833))
PROC_FOPS_RW(pbm_debug_log_reduc);
#endif
PROC_FOPS_RW(pbm_manual_mode);

static int mt_pbm_create_procfs(void)
{
	struct proc_dir_entry *dir = NULL;
	int i;

	struct pentry {
		const char *name;
		const struct file_operations *fops;
	};

	const struct pentry entries[] = {
		PROC_ENTRY(pbm_debug),
		PROC_ENTRY(pbm_stop),
#if (defined(CONFIG_MACH_MT6877) \
	|| defined(CONFIG_MACH_MT6768) \
	|| defined(CONFIG_MACH_MT6781) \
	|| defined(CONFIG_MACH_MT6833))
	PROC_ENTRY(pbm_debug_log_reduc),
#endif
		PROC_ENTRY(pbm_manual_mode),
	};

	dir = proc_mkdir("pbm", NULL);

	if (!dir) {
		pr_err("fail to create /proc/pbm @ %s()\n", __func__);
		return -ENOMEM;
	}

	for (i = 0; i < ARRAY_SIZE(entries); i++) {
		if (!proc_create
		    (entries[i].name, 0664, dir, entries[i].fops))
			pr_err("@%s: create /proc/pbm/%s failed\n", __func__,
				    entries[i].name);
	}

	return 0;
}
/* CONFIG_PBM_PROC_FS */

static int __init pbm_module_init(void)
{
	int ret = 0;

	/* CONFIG_PBM_PROC_FS */
	mt_pbm_create_procfs();

	pm_notifier(_mt_pbm_pm_callback, 0);

	register_dlpt_notify(&kicker_pbm_by_dlpt, DLPT_PRIO_PBM);
	ret = create_pbm_kthread();
	if (ret) {
		pr_notice("FAILED TO CREATE PBM KTHREAD\n");
		return ret;
	}

	#ifdef MD_POWER_UT
	/* pr_info("share_reg: %x", spm_vcorefs_get_MD_status());*/
	mt_pbm_debug = 1;
	md_power_meter_ut();
	#endif

	pr_info("%s : Done\n", __func__);

	return ret;
}

#else				/* #ifndef DISABLE_PBM_FEATURE */

void kicker_pbm_by_dlpt(int i_max)
{
}

void kicker_pbm_by_md(enum pbm_kicker kicker, bool status)
{
}

void kicker_pbm_by_cpu(unsigned int loading, int core, int voltage)
{
}

void kicker_pbm_by_gpu(bool status, unsigned int loading, int voltage)
{
}

void kicker_pbm_by_flash(bool status)
{
}

static int __init pbm_module_init(void)
{
	pr_notice("DISABLE_PBM_FEATURE is defined.\n");
	return 0;
}

#endif				/* #ifndef DISABLE_PBM_FEATURE */

static void __exit pbm_module_exit(void)
{

}

module_init(pbm_module_init);
module_exit(pbm_module_exit);

MODULE_DESCRIPTION("PBM Driver v0.1");
