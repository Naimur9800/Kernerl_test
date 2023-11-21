/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
*/

/* This file is generated by GenLP_setting.pl v1.5.7 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

const unsigned int AP_CG_Golden_Setting_tcl_gs_dpidle_data[] = {
/*  Address	 Mask		Golden Setting Value */
	0xC53C8A0, 0x2, 0x2,/* MP0_DCM_CFG8 */
	0xC53C8A0, 0x2, 0x2,/* MP0_DCM_CFG8 */
	0x10000000, 0xF00, 0x0,/* CLK_MODE */
	0x10000010, 0x80808080, 0x800000,/* CLK_CFG_0 */
	0x10000020, 0x80808080, 0x80808080,/* CLK_CFG_1 */
	0x10000030, 0x80808080, 0x80808080,/* CLK_CFG_2 */
	0x10000040, 0x80808080, 0x80808080,/* CLK_CFG_3 */
	0x10000050, 0x80808080, 0x80808080,/* CLK_CFG_4 */
	0x10000060, 0x80808080, 0x80808080,/* CLK_CFG_5 */
	0x10000070, 0x80808080, 0x80808080,/* CLK_CFG_6 */
	0x10000080, 0x80808080, 0x808080,/* CLK_CFG_7 */
	0x10000090, 0x80808080, 0x80800080,/* CLK_CFG_8 */
	0x100000A0, 0x80808080, 0x80808080,/* CLK_CFG_9 */
	0x100000B0, 0x80808080, 0x80808080,/* CLK_CFG_10 */
	0x100000C0, 0x80808080, 0x80808080,/* CLK_CFG_11 */
	0x100000D0, 0x80808080, 0x80808080,/* CLK_CFG_12 */
	0x100000E0, 0x80808080, 0x80808080,/* CLK_CFG_13 */
	0x100000F0, 0x80808080, 0x800080,/* CLK_CFG_14 */
	0x10000100, 0x808080, 0x0,/* CLK_CFG_15 */
	0x10000110, 0x800080, 0x800080,/* CLK_CFG_16 */
	0x10000140, 0x3030, 0x3000,/* CLK_MISC_CFG_0 */
	0x10000180, 0x8080, 0x8000,/* CLK_CFG_17 */
	0x10000320, 0x7FF, 0x7FF,/* CLK_AUDDIV_0 */
	0x10001070, 0x4, 0x0,/* INFRA_BUS_DCM_CTRL */
	0x10001074, 0x4, 0x0,/* PERI_BUS_DCM_CTRL */
	0x10001080, 0x9BEFFFFF, 0x9BEFFFF0,/* MODULE_SW_CG_0_SET */
	0x10001084, 0x9BEFFFFF, 0x0,/* MODULE_SW_CG_0_CLR */
	0x10001088, 0xFF9FFFD6, 0x7A1F8B56,/* MODULE_SW_CG_1_SET */
	0x1000108C, 0xFF9FFFD7, 0x0,/* MODULE_SW_CG_1_CLR */
	0x100010A4, 0xFFFFFEFF, 0xFFFFFEFF,/* MODULE_SW_CG_2_SET */
	0x100010A8, 0xFFFFFEFF, 0x0,/* MODULE_SW_CG_2_CLR */
	0x100010C0, 0xFFFFCFFF, 0xCFF0C9FF,/* MODULE_SW_CG_3_SET */
	0x100010C4, 0xFFFFCFFF, 0x300000,/* MODULE_SW_CG_3_CLR */
	0x100010E0, 0xFFFF017F, 0xFFFF017F,/* MODULE_SW_CG_4_SET */
	0x100010E4, 0xFFFF01FF, 0x0,/* MODULE_SW_CG_4_CLR */
	0x10002028, 0x7F0000, 0x0,/* INFRA_EMI_DCM_CFG0 */
	0x10002038, 0xFFFFFFFF, 0x0,/* TOP_CK_ANCHOR_CFG */
	0x1000320C, 0x80000000, 0x0,/* PERIAXI_SI0_CTL */
	0x1000C000, 0x1, 0x1,/* AP_PLL_CON0 */
	0x1000C008, 0xE0000000, 0xE0000000,/* AP_PLL_CON2 */
	0x1000C00C, 0x1E, 0x0,/* AP_PLL_CON3 */
	0x1000C014, 0x3EBF8, 0x20A0,/* AP_PLL_CON5 */
	0x1000C200, 0xFFFFFF, 0xFFFFFF,/* AP_PLLGP1_CON0 */
	0x1000C208, 0x1, 0x1,/* ARMPLL_LL_CON0 */
	0x1000C218, 0x1, 0x1,/* ARMPLL_BL_CON0 */
	0x1000C228, 0x1, 0x1,/* ARMPLL_B_CON0 */
	0x1000C238, 0x1, 0x1,/* CCIPLL_CON0 */
	0x1000C248, 0x1, 0x0,/* TVDPLL_CON0 */
	0x1000C300, 0x3FFFFFF, 0x3C00680,/* AP_PLLGP2_CON0 */
	0x1000C308, 0xFF000001, 0xFC000000,/* UNIVPLL_CON0 */
	0x1000C318, 0x1, 0x0,/* USBPLL_CON0 */
	0x1000C328, 0x1, 0x0,/* APLL1_CON0 */
	0x1000C33C, 0x1, 0x0,/* APLL2_CON0 */
	0x1000C350, 0x7F000001, 0x7C000001,/* MAINPLL_CON0 */
	0x1000C360, 0x1, 0x0,/* MSDCPLL_CON0 */
	0x1000C370, 0x1, 0x0,/* IMGPLL_CON0 */
	0x1000C380, 0x1, 0x0,/* ADSPPLL_CON0 */
	0x1000C390, 0x1, 0x1,/* MPLL_CON0 */
	0x1000C3A0, 0xFF000001, 0x0,/* MMPLL_CON0 */
	0x1000C3B0, 0x1, 0x0,/* EMIPLL_CON0 */
	0x10012000, 0x1, 0x0,/* DVFSRC_BASIC_CONTROL */
	0x1020EB00, 0x7, 0x0,/* BUS_MON_CKEN */
	0x10219834, 0x3, 0x0,/* EMI_THRO_PRD0 */
	0x10219838, 0xFF0000, 0x0,/* EMI_THRO_PRD1 */
	0x10219858, 0x800, 0x0,/* EMI_THRO_CTRL1 */
	0x1021C210, 0xF, 0x0,/* BUS_MEM_MON_CKEN */
	0x102280F0, 0xFFFF0000, 0x10000,/* GCE_CTL_INT0 */
	0x10238164, 0x10000000, 0x10000000,/* B0_RXDVS0 */
	0x102382E4, 0x10000000, 0x10000000,/* B1_RXDVS0 */
	0x10238464, 0x10000000, 0x10000000,/* CA_RXDVS0 */
	0x102384EC, 0x500000, 0x0,/* MISC_CG_CTRL0 */
	0x102384F0, 0xFFFFFFFF, 0xFFFFFFFF,/* MISC_CG_CTRL1 */
	0x102384F8, 0xFFFFFFFF, 0x0,/* MISC_CG_CTRL3 */
	0x10238504, 0x800, 0x0,/* MISC_CG_CTRL7 */
	0x10238508, 0x8800, 0x8800,/* MISC_CG_CTRL9 */
	0x10238624, 0x8, 0x8,/* MISC_DUTYSCAN1 */
	0x10238670, 0x8, 0x8,/* MISC_RX_AUTOK_CFG0 */
	0x10238860, 0x4, 0x4,/* SHU_B0_DQ0 */
	0x102389E0, 0x4, 0x4,/* SHU_B1_DQ0 */
	0x10238B60, 0x4, 0x4,/* SHU_CA_CMD0 */
	0x10238D90, 0x20000, 0x0,/* MISC_SHU_DLINE_MON_CTRL */
	0x10238DA0, 0x730, 0x620,/* MISC_SHU_RX_CG_CTRL */
	0x10248164, 0x10000000, 0x10000000,/* B0_RXDVS0 */
	0x102482E4, 0x10000000, 0x10000000,/* B1_RXDVS0 */
	0x10248464, 0x10000000, 0x10000000,/* CA_RXDVS0 */
	0x102484EC, 0x500000, 0x0,/* MISC_CG_CTRL0 */
	0x102484F0, 0xFFFFFFFF, 0xFFFFFFFF,/* MISC_CG_CTRL1 */
	0x102484F8, 0xFFFFFFFF, 0x0,/* MISC_CG_CTRL3 */
	0x10248504, 0x800, 0x0,/* MISC_CG_CTRL7 */
	0x10248508, 0x8800, 0x8800,/* MISC_CG_CTRL9 */
	0x10248624, 0x8, 0x8,/* MISC_DUTYSCAN1 */
	0x10248670, 0x8, 0x8,/* MISC_RX_AUTOK_CFG0 */
	0x10248860, 0x4, 0x4,/* SHU_B0_DQ0 */
	0x102489E0, 0x4, 0x4,/* SHU_B1_DQ0 */
	0x10248B60, 0x4, 0x4,/* SHU_CA_CMD0 */
	0x10248D90, 0x20000, 0x0,/* MISC_SHU_DLINE_MON_CTRL */
	0x10248DA0, 0x730, 0x620,/* MISC_SHU_RX_CG_CTRL */
	0x10443000, 0x1FEBFE, 0x4000,/* SSPM_CK_EN */
	0x10443010, 0x1, 0x0,/* SSPM_UART_CTRL */
	0x10720180, 0x1, 0x1,/* AUDIODSP_CK_CG */
	0x10801000, 0xCFB, 0x0,/* ADSP_CK_EN */
	0x10801010, 0x1, 0x0,/* ADSP_UART_CTRL */
	0x10943000, 0x1000, 0x0,/* SSPM_CK_EN */
	0x10943004, 0x100, 0x100,/* SSPM_MCLK_DIV */
	0x10943010, 0x1, 0x0,/* SSPM_UART_CTRL */
	0x1100B0E4, 0x1, 0x0,/* LVTSCLKEN_0 */
	0x1100B1E4, 0x1, 0x0,/* LVTSCLKEN_1 */
	0x1100B2E4, 0x1, 0x0,/* LVTSCLKEN_2 */
	0x1100BF00, 0x803F0000, 0x0,/*  */
	0x11201C84, 0x4, 0x4,/* MISC_CTRL */
	0x11203E30, 0x1, 0x1,/* SSUSB_U3_CTRL_0P */
	0x11203E50, 0x1, 0x1,/* SSUSB_U2_CTRL_0P */
	0x11203E80, 0x1, 0x1,/* SSUSB_DMA_CTRL */
	0x11210000, 0x1F1C0304, 0x1F1C0304,/* AUDIO_TOP_CON0 */
	0x11210004, 0xF033F0F0, 0xF033F0F0,/* AUDIO_TOP_CON1 */
	0x11210008, 0x1F, 0x1F,/* AUDIO_TOP_CON2 */
	0x11230068, 0x1, 0x0,/* MSDC_NEW_RX_CFG */
	0x112300B4, 0x400000, 0x0,/* PATCH_BIT1 */
	0x11270144, 0x1, 0x0,/* UFS_ADDR_XOUFS_ST */
	0x112780E4, 0x1, 0x0,/* LVTSCLKEN_0 */
	0x112781E4, 0x1, 0x0,/* LVTSCLKEN_1 */
	0x11278F00, 0x803F0000, 0x0,/*  */
	0x11282E00, 0x3, 0x3,/* AP_CLOCK_CG_RO_CEN */
	0x11282E04, 0x3, 0x0,/* AP_CLOCK_CG_W1C_CEN */
	0x11282E08, 0x3, 0x3,/* AP_CLOCK_CG_W1S_CEN */
	0x11C7004C, 0x80000000, 0x0,/* MSDC_TOP_TEST_CFG2 */
	0x11CB1E00, 0x1, 0x1,/* AP_CLOCK_CG_RO_EST */
	0x11CB1E04, 0x1, 0x0,/* AP_CLOCK_CG_W1C_EST */
	0x11CB1E08, 0x1, 0x1,/* AP_CLOCK_CG_W1S_EST */
	0x11D04E00, 0xF, 0xF,/* AP_CLOCK_CG_RO_SOU */
	0x11D04E04, 0xF, 0x0,/* AP_CLOCK_CG_W1C_SOU */
	0x11D04E08, 0xF, 0xF,/* AP_CLOCK_CG_W1S_SOU */
	0x11D23E00, 0x7, 0x7,/* AP_CLOCK_CG_RO_WEST_SOU */
	0x11D23E04, 0x7, 0x0,/* AP_CLOCK_CG_W1C_WEST_SOU */
	0x11D23E08, 0x7, 0x7,/* AP_CLOCK_CG_W1S_WEST_SOU */
	0x11E01E00, 0x1, 0x1,/* AP_CLOCK_CG_RO_WST */
	0x11E01E04, 0x1, 0x0,/* AP_CLOCK_CG_W1C_WST */
	0x11E01E08, 0x1, 0x1,/* AP_CLOCK_CG_W1S_WST */
	0x11E40380, 0x1, 0x0,/* U2PHYBC12C */
	0x11F01E00, 0x1, 0x1,/* AP_CLOCK_CG_RO_NOR */
	0x11F01E04, 0x1, 0x0,/* AP_CLOCK_CG_W1C_NOR */
	0x11F01E08, 0x1, 0x1,/* AP_CLOCK_CG_W1S_NOR */
	0x11F5004C, 0x80000000, 0x0,/* MSDC_TOP_TEST_CFG2 */
	0x13FBF004, 0x1, 0x1,/* MFG_CG_SET */
	0x13FBF008, 0x1, 0x0,/* MFG_CG_CLR */
	0x14000100, 0xFFFFFFFF, 0xFFFFFFFF,/* MMSYS_CG_CON0 */
	0x14000110, 0xFFFFFFFF, 0xFFFFFFFF,/* MMSYS_CG_CON1 */
	0x140001A0, 0xFFFFFFFF, 0xFFFFFFFF,/* MMSYS_CG_CON2 */
	0x15020000, 0x1007, 0x1007,/* IMG_CG_CON */
	0x15820000, 0x11C3, 0x11C3,/* IMG_CG_CON */
	0x1602F000, 0x1, 0x0,/* VDEC_CKEN_SET */
	0x1602F004, 0x1, 0x1,/* VDEC_CKEN_CLR */
	0x1602F008, 0x1, 0x0,/* LARB_CKEN_CON_SET */
	0x1602F00C, 0x1, 0x1,/* LARB_CKEN_CON_CLR */
	0x1602F200, 0x1, 0x0,/* LAT_CKEN_SET */
	0x1602F204, 0x1, 0x1,/* LAT_CKEN_CLR */
	0x17000000, 0x10000111, 0x0,/* VENCSYS_CG_CON */
	0x17000004, 0x10000111, 0x0,/* VENCSYS_CG_SET */
	0x17000008, 0x10000111, 0x10000111,/* VENCSYS_CG_CLR */
	0x19020000, 0x7FFFE, 0x7FFFE,/* APU_CONN_CG_CON */
	0x19024000, 0x37, 0x37,/* APU_CONN1_CG_CON */
	0x19029000, 0xF, 0xF,/* APUSYS_VCORE_CG_CON */
	0x19030100, 0x7, 0x7,/* CORE_CG_CON */
	0x19031100, 0x7, 0x7,/* CORE_CG_CON */
	0x19034000, 0x181FFF, 0x181FFF,/* MDLA_CG_CON */
	0x1A000000, 0xFFDCF, 0xFFDCF,/* CAMSYS_CG_CON */
	0x1A04F000, 0x7, 0x7,/* CAMSYS_CG_CON */
	0x1A06F000, 0x7, 0x7,/* CAMSYS_CG_CON */
	0x1B000000, 0x17F, 0x17F,/* IMG_CG_CON */
	0x1F000100, 0xFFFFFFFF, 0xFFFFFFFF,/* MDPSYS_CG_CON0 */
	0x1F000110, 0xFFFFFFFF, 0xFFFFFFFF,/* MDPSYS_CG_CON1 */
	0x1F000120, 0xFFFFFFFF, 0xFFFFFFFF,/* MDPSYS_CG_CON2 */
	0x1F000130, 0xFFFFFFFF, 0xFFFFFFFF,/* MDPSYS_CG_CON3 */
	0x1F000140, 0xFFFFFFFF, 0xFFFFFFFF /* MDPSYS_CG_CON4 */
};

const unsigned int *AP_CG_Golden_Setting_tcl_gs_dpidle =
		AP_CG_Golden_Setting_tcl_gs_dpidle_data;

unsigned int AP_CG_Golden_Setting_tcl_gs_dpidle_len = 522;

const unsigned int AP_CG_Golden_Setting_tcl_gs_suspend_data[] = {
/*  Address	 Mask		Golden Setting Value */
	0xC53C8A0, 0x2, 0x2,/* MP0_DCM_CFG8 */
	0xC53C8A0, 0x2, 0x2,/* MP0_DCM_CFG8 */
	0x10000000, 0xF00, 0x0,/* CLK_MODE */
	0x10000010, 0x80808080, 0x800000,/* CLK_CFG_0 */
	0x10000020, 0x80808080, 0x80808080,/* CLK_CFG_1 */
	0x10000030, 0x80808080, 0x80808080,/* CLK_CFG_2 */
	0x10000040, 0x80808080, 0x80808080,/* CLK_CFG_3 */
	0x10000050, 0x80808080, 0x80808080,/* CLK_CFG_4 */
	0x10000060, 0x80808080, 0x80808080,/* CLK_CFG_5 */
	0x10000070, 0x80808080, 0x80808080,/* CLK_CFG_6 */
	0x10000080, 0x80808080, 0x808080,/* CLK_CFG_7 */
	0x10000090, 0x80808080, 0x80800080,/* CLK_CFG_8 */
	0x100000A0, 0x80808080, 0x80808080,/* CLK_CFG_9 */
	0x100000B0, 0x80808080, 0x80808080,/* CLK_CFG_10 */
	0x100000C0, 0x80808080, 0x80808080,/* CLK_CFG_11 */
	0x100000D0, 0x80808080, 0x80808080,/* CLK_CFG_12 */
	0x100000E0, 0x80808080, 0x80808080,/* CLK_CFG_13 */
	0x100000F0, 0x80808080, 0x800080,/* CLK_CFG_14 */
	0x10000100, 0x808080, 0x0,/* CLK_CFG_15 */
	0x10000110, 0x800080, 0x800080,/* CLK_CFG_16 */
	0x10000140, 0x3030, 0x3000,/* CLK_MISC_CFG_0 */
	0x10000180, 0x8080, 0x8080,/* CLK_CFG_17 */
	0x10000320, 0x7FF, 0x7FF,/* CLK_AUDDIV_0 */
	0x10001070, 0x4, 0x0,/* INFRA_BUS_DCM_CTRL */
	0x10001074, 0x4, 0x0,/* PERI_BUS_DCM_CTRL */
	0x10001080, 0x9BEFFFFF, 0x9BEFFFF0,/* MODULE_SW_CG_0_SET */
	0x10001084, 0x9BEFFFFF, 0x0,/* MODULE_SW_CG_0_CLR */
	0x10001088, 0xFF9FFFD6, 0x7A1F8B56,/* MODULE_SW_CG_1_SET */
	0x1000108C, 0xFF9FFFD7, 0x0,/* MODULE_SW_CG_1_CLR */
	0x100010A4, 0xFFFFFEFF, 0xFFFFFEFF,/* MODULE_SW_CG_2_SET */
	0x100010A8, 0xFFFFFEFF, 0x0,/* MODULE_SW_CG_2_CLR */
	0x100010C0, 0xFFFFCFFF, 0xCFF0C9FF,/* MODULE_SW_CG_3_SET */
	0x100010C4, 0xFFFFCFFF, 0x300000,/* MODULE_SW_CG_3_CLR */
	0x100010E0, 0xFFFF017F, 0xFFFF017F,/* MODULE_SW_CG_4_SET */
	0x100010E4, 0xFFFF01FF, 0x0,/* MODULE_SW_CG_4_CLR */
	0x10002028, 0x7F0000, 0x0,/* INFRA_EMI_DCM_CFG0 */
	0x10002038, 0xFFFFFFFF, 0x0,/* TOP_CK_ANCHOR_CFG */
	0x1000320C, 0x80000000, 0x0,/* PERIAXI_SI0_CTL */
	0x1000C000, 0x1, 0x1,/* AP_PLL_CON0 */
	0x1000C008, 0xE0000000, 0xE0000000,/* AP_PLL_CON2 */
	0x1000C00C, 0x1E, 0x0,/* AP_PLL_CON3 */
	0x1000C014, 0x3EBF8, 0x20A0,/* AP_PLL_CON5 */
	0x1000C200, 0xFFFFFF, 0xFFFFFF,/* AP_PLLGP1_CON0 */
	0x1000C208, 0x1, 0x1,/* ARMPLL_LL_CON0 */
	0x1000C218, 0x1, 0x1,/* ARMPLL_BL_CON0 */
	0x1000C228, 0x1, 0x1,/* ARMPLL_B_CON0 */
	0x1000C238, 0x1, 0x1,/* CCIPLL_CON0 */
	0x1000C248, 0x1, 0x0,/* TVDPLL_CON0 */
	0x1000C300, 0x3FFFFFF, 0x3C007FF,/* AP_PLLGP2_CON0 */
	0x1000C308, 0xFF000001, 0xFC000000,/* UNIVPLL_CON0 */
	0x1000C318, 0x1, 0x0,/* USBPLL_CON0 */
	0x1000C328, 0x1, 0x0,/* APLL1_CON0 */
	0x1000C33C, 0x1, 0x0,/* APLL2_CON0 */
	0x1000C350, 0x7F000001, 0x7C000001,/* MAINPLL_CON0 */
	0x1000C360, 0x1, 0x0,/* MSDCPLL_CON0 */
	0x1000C370, 0x1, 0x0,/* IMGPLL_CON0 */
	0x1000C380, 0x1, 0x0,/* ADSPPLL_CON0 */
	0x1000C390, 0x1, 0x1,/* MPLL_CON0 */
	0x1000C3A0, 0xFF000001, 0x0,/* MMPLL_CON0 */
	0x1000C3B0, 0x1, 0x0,/* EMIPLL_CON0 */
	0x10012000, 0x1, 0x0,/* DVFSRC_BASIC_CONTROL */
	0x1020EB00, 0x7, 0x0,/* BUS_MON_CKEN */
	0x10219834, 0x3, 0x0,/* EMI_THRO_PRD0 */
	0x10219838, 0xFF0000, 0x0,/* EMI_THRO_PRD1 */
	0x10219858, 0x800, 0x0,/* EMI_THRO_CTRL1 */
	0x1021C210, 0xF, 0x0,/* BUS_MEM_MON_CKEN */
	0x102280F0, 0xFFFF0000, 0x10000,/* GCE_CTL_INT0 */
	0x10238164, 0x10000000, 0x10000000,/* B0_RXDVS0 */
	0x102382E4, 0x10000000, 0x10000000,/* B1_RXDVS0 */
	0x10238464, 0x10000000, 0x10000000,/* CA_RXDVS0 */
	0x102384EC, 0x500000, 0x0,/* MISC_CG_CTRL0 */
	0x102384F0, 0xFFFFFFFF, 0xFFFFFFFF,/* MISC_CG_CTRL1 */
	0x102384F8, 0xFFFFFFFF, 0x0,/* MISC_CG_CTRL3 */
	0x10238504, 0x800, 0x0,/* MISC_CG_CTRL7 */
	0x10238508, 0x8800, 0x8800,/* MISC_CG_CTRL9 */
	0x10238624, 0x8, 0x8,/* MISC_DUTYSCAN1 */
	0x10238670, 0x8, 0x8,/* MISC_RX_AUTOK_CFG0 */
	0x10238860, 0x4, 0x4,/* SHU_B0_DQ0 */
	0x102389E0, 0x4, 0x4,/* SHU_B1_DQ0 */
	0x10238B60, 0x4, 0x4,/* SHU_CA_CMD0 */
	0x10238D90, 0x20000, 0x0,/* MISC_SHU_DLINE_MON_CTRL */
	0x10238DA0, 0x730, 0x620,/* MISC_SHU_RX_CG_CTRL */
	0x10248164, 0x10000000, 0x10000000,/* B0_RXDVS0 */
	0x102482E4, 0x10000000, 0x10000000,/* B1_RXDVS0 */
	0x10248464, 0x10000000, 0x10000000,/* CA_RXDVS0 */
	0x102484EC, 0x500000, 0x0,/* MISC_CG_CTRL0 */
	0x102484F0, 0xFFFFFFFF, 0xFFFFFFFF,/* MISC_CG_CTRL1 */
	0x102484F8, 0xFFFFFFFF, 0x0,/* MISC_CG_CTRL3 */
	0x10248504, 0x800, 0x0,/* MISC_CG_CTRL7 */
	0x10248508, 0x8800, 0x8800,/* MISC_CG_CTRL9 */
	0x10248624, 0x8, 0x8,/* MISC_DUTYSCAN1 */
	0x10248670, 0x8, 0x8,/* MISC_RX_AUTOK_CFG0 */
	0x10248860, 0x4, 0x4,/* SHU_B0_DQ0 */
	0x102489E0, 0x4, 0x4,/* SHU_B1_DQ0 */
	0x10248B60, 0x4, 0x4,/* SHU_CA_CMD0 */
	0x10248D90, 0x20000, 0x0,/* MISC_SHU_DLINE_MON_CTRL */
	0x10248DA0, 0x730, 0x620,/* MISC_SHU_RX_CG_CTRL */
	0x10443000, 0x1FEBFE, 0x4000,/* SSPM_CK_EN */
	0x10443010, 0x1, 0x0,/* SSPM_UART_CTRL */
	0x10720180, 0x1, 0x1,/* AUDIODSP_CK_CG */
	0x10801000, 0xCFB, 0x0,/* ADSP_CK_EN */
	0x10801010, 0x1, 0x0,/* ADSP_UART_CTRL */
	0x10943000, 0x1000, 0x0,/* SSPM_CK_EN */
	0x10943004, 0x100, 0x100,/* SSPM_MCLK_DIV */
	0x10943010, 0x1, 0x0,/* SSPM_UART_CTRL */
	0x1100B0E4, 0x1, 0x0,/* LVTSCLKEN_0 */
	0x1100B1E4, 0x1, 0x0,/* LVTSCLKEN_1 */
	0x1100B2E4, 0x1, 0x0,/* LVTSCLKEN_2 */
	0x1100BF00, 0x803F0000, 0x0,/*  */
	0x11201C84, 0x4, 0x4,/* MISC_CTRL */
	0x11203E30, 0x1, 0x1,/* SSUSB_U3_CTRL_0P */
	0x11203E50, 0x1, 0x1,/* SSUSB_U2_CTRL_0P */
	0x11203E80, 0x1, 0x1,/* SSUSB_DMA_CTRL */
	0x11210000, 0x1F1C0304, 0x1F1C0304,/* AUDIO_TOP_CON0 */
	0x11210004, 0xF033F0F0, 0xF033F0F0,/* AUDIO_TOP_CON1 */
	0x11210008, 0x1F, 0x1F,/* AUDIO_TOP_CON2 */
	0x11230068, 0x1, 0x0,/* MSDC_NEW_RX_CFG */
	0x112300B4, 0x400000, 0x0,/* PATCH_BIT1 */
	0x11270144, 0x1, 0x0,/* UFS_ADDR_XOUFS_ST */
	0x112780E4, 0x1, 0x0,/* LVTSCLKEN_0 */
	0x112781E4, 0x1, 0x0,/* LVTSCLKEN_1 */
	0x11278F00, 0x803F0000, 0x0,/*  */
	0x11282E00, 0x3, 0x3,/* AP_CLOCK_CG_RO_CEN */
	0x11282E04, 0x3, 0x0,/* AP_CLOCK_CG_W1C_CEN */
	0x11282E08, 0x3, 0x3,/* AP_CLOCK_CG_W1S_CEN */
	0x11C7004C, 0x80000000, 0x0,/* MSDC_TOP_TEST_CFG2 */
	0x11CB1E00, 0x1, 0x1,/* AP_CLOCK_CG_RO_EST */
	0x11CB1E04, 0x1, 0x0,/* AP_CLOCK_CG_W1C_EST */
	0x11CB1E08, 0x1, 0x1,/* AP_CLOCK_CG_W1S_EST */
	0x11D04E00, 0xF, 0xF,/* AP_CLOCK_CG_RO_SOU */
	0x11D04E04, 0xF, 0x0,/* AP_CLOCK_CG_W1C_SOU */
	0x11D04E08, 0xF, 0xF,/* AP_CLOCK_CG_W1S_SOU */
	0x11D23E00, 0x7, 0x7,/* AP_CLOCK_CG_RO_WEST_SOU */
	0x11D23E04, 0x7, 0x0,/* AP_CLOCK_CG_W1C_WEST_SOU */
	0x11D23E08, 0x7, 0x7,/* AP_CLOCK_CG_W1S_WEST_SOU */
	0x11E01E00, 0x1, 0x1,/* AP_CLOCK_CG_RO_WST */
	0x11E01E04, 0x1, 0x0,/* AP_CLOCK_CG_W1C_WST */
	0x11E01E08, 0x1, 0x1,/* AP_CLOCK_CG_W1S_WST */
	0x11E40380, 0x1, 0x0,/* U2PHYBC12C */
	0x11F01E00, 0x1, 0x1,/* AP_CLOCK_CG_RO_NOR */
	0x11F01E04, 0x1, 0x0,/* AP_CLOCK_CG_W1C_NOR */
	0x11F01E08, 0x1, 0x1,/* AP_CLOCK_CG_W1S_NOR */
	0x11F5004C, 0x80000000, 0x0,/* MSDC_TOP_TEST_CFG2 */
	0x13FBF004, 0x1, 0x1,/* MFG_CG_SET */
	0x13FBF008, 0x1, 0x0,/* MFG_CG_CLR */
	0x14000100, 0xFFFFFFFF, 0xFFFFFFFF,/* MMSYS_CG_CON0 */
	0x14000110, 0xFFFFFFFF, 0xFFFFFFFF,/* MMSYS_CG_CON1 */
	0x140001A0, 0xFFFFFFFF, 0xFFFFFFFF,/* MMSYS_CG_CON2 */
	0x15020000, 0x1007, 0x1007,/* IMG_CG_CON */
	0x15811058, 0x3FFFF, 0x0,/* CTL_WPE_DCM_DIS */
	0x1581105C, 0x1F, 0x0,/* CTL_DMA_DCM_DIS */
	0x15820000, 0x11C3, 0x11C3,/* IMG_CG_CON */
	0x1602F000, 0x1, 0x0,/* VDEC_CKEN_SET */
	0x1602F004, 0x1, 0x1,/* VDEC_CKEN_CLR */
	0x1602F008, 0x1, 0x0,/* LARB_CKEN_CON_SET */
	0x1602F00C, 0x1, 0x1,/* LARB_CKEN_CON_CLR */
	0x1602F200, 0x1, 0x0,/* LAT_CKEN_SET */
	0x1602F204, 0x1, 0x1,/* LAT_CKEN_CLR */
	0x17000000, 0x10000111, 0x0,/* VENCSYS_CG_CON */
	0x17000004, 0x10000111, 0x0,/* VENCSYS_CG_SET */
	0x17000008, 0x10000111, 0x10000111,/* VENCSYS_CG_CLR */
	0x19020000, 0x7FFFE, 0x7FFFE,/* APU_CONN_CG_CON */
	0x19024000, 0x37, 0x37,/* APU_CONN1_CG_CON */
	0x19029000, 0xF, 0xF,/* APUSYS_VCORE_CG_CON */
	0x19030100, 0x7, 0x7,/* CORE_CG_CON */
	0x19031100, 0x7, 0x7,/* CORE_CG_CON */
	0x19034000, 0x181FFF, 0x181FFF,/* MDLA_CG_CON */
	0x1A000000, 0xFFDCF, 0xFFDCF,/* CAMSYS_CG_CON */
	0x1A04F000, 0x7, 0x7,/* CAMSYS_CG_CON */
	0x1A06F000, 0x7, 0x7,/* CAMSYS_CG_CON */
	0x1B000000, 0x17F, 0x17F,/* IMG_CG_CON */
	0x1F000100, 0xFFFFFFFF, 0xFFFFFFFF,/* MDPSYS_CG_CON0 */
	0x1F000110, 0xFFFFFFFF, 0xFFFFFFFF,/* MDPSYS_CG_CON1 */
	0x1F000120, 0xFFFFFFFF, 0xFFFFFFFF,/* MDPSYS_CG_CON2 */
	0x1F000130, 0xFFFFFFFF, 0xFFFFFFFF,/* MDPSYS_CG_CON3 */
	0x1F000140, 0xFFFFFFFF, 0xFFFFFFFF /* MDPSYS_CG_CON4 */
};

const unsigned int *AP_CG_Golden_Setting_tcl_gs_suspend =
		AP_CG_Golden_Setting_tcl_gs_suspend_data;

unsigned int AP_CG_Golden_Setting_tcl_gs_suspend_len = 528;

const unsigned int AP_CG_Golden_Setting_tcl_gs_sodi_data[] = {
/*  Address	 Mask		Golden Setting Value */
	0x10012000, 0x1, 0x1,/* DVFSRC_BASIC_CONTROL */
	0x10219834, 0x3, 0x3,/* EMI_THRO_PRD0 */
	0x10219838, 0xFF0000, 0x4D0000,/* EMI_THRO_PRD1 */
	0x10219858, 0x800, 0x800,/* EMI_THRO_CTRL1 */
	0x10238164, 0x10000000, 0x10000000,/* B0_RXDVS0 */
	0x102382E4, 0x10000000, 0x10000000,/* B1_RXDVS0 */
	0x10238464, 0x10000000, 0x10000000,/* CA_RXDVS0 */
	0x102384EC, 0x500000, 0x0,/* MISC_CG_CTRL0 */
	0x102384F0, 0xFFFFFFFF, 0xFFFFFFFF,/* MISC_CG_CTRL1 */
	0x102384F8, 0xFFFFFFFF, 0x0,/* MISC_CG_CTRL3 */
	0x10238504, 0x800, 0x0,/* MISC_CG_CTRL7 */
	0x10238508, 0x8800, 0x8800,/* MISC_CG_CTRL9 */
	0x10238624, 0x8, 0x8,/* MISC_DUTYSCAN1 */
	0x10238670, 0x8, 0x8,/* MISC_RX_AUTOK_CFG0 */
	0x10238860, 0x4, 0x4,/* SHU_B0_DQ0 */
	0x102389E0, 0x4, 0x4,/* SHU_B1_DQ0 */
	0x10238B60, 0x4, 0x4,/* SHU_CA_CMD0 */
	0x10238D90, 0x20000, 0x0,/* MISC_SHU_DLINE_MON_CTRL */
	0x10238DA0, 0x730, 0x620,/* MISC_SHU_RX_CG_CTRL */
	0x10248164, 0x10000000, 0x10000000,/* B0_RXDVS0 */
	0x102482E4, 0x10000000, 0x10000000,/* B1_RXDVS0 */
	0x10248464, 0x10000000, 0x10000000,/* CA_RXDVS0 */
	0x102484EC, 0x500000, 0x0,/* MISC_CG_CTRL0 */
	0x102484F0, 0xFFFFFFFF, 0xFFFFFFFF,/* MISC_CG_CTRL1 */
	0x102484F8, 0xFFFFFFFF, 0x0,/* MISC_CG_CTRL3 */
	0x10248504, 0x800, 0x0,/* MISC_CG_CTRL7 */
	0x10248508, 0x8800, 0x8800,/* MISC_CG_CTRL9 */
	0x10248624, 0x8, 0x8,/* MISC_DUTYSCAN1 */
	0x10248670, 0x8, 0x8,/* MISC_RX_AUTOK_CFG0 */
	0x10248860, 0x4, 0x4,/* SHU_B0_DQ0 */
	0x102489E0, 0x4, 0x4,/* SHU_B1_DQ0 */
	0x10248B60, 0x4, 0x4,/* SHU_CA_CMD0 */
	0x10248D90, 0x20000, 0x0,/* MISC_SHU_DLINE_MON_CTRL */
	0x10248DA0, 0x730, 0x620,/* MISC_SHU_RX_CG_CTRL */
	0x10720180, 0x1, 0x1,/* AUDIODSP_CK_CG */
	0x11230068, 0x1, 0x0,/* MSDC_NEW_RX_CFG */
	0x112300B4, 0x400000, 0x400000,/* PATCH_BIT1 */
	0x11C7004C, 0x80000000, 0x0,/* MSDC_TOP_TEST_CFG2 */
	0x11F5004C, 0x80000000, 0x0,/* MSDC_TOP_TEST_CFG2 */
	0x14000100, 0xFFFFFFFF, 0x0,/* MMSYS_CG_CON0 */
	0x14000110, 0xFFFFFFFF, 0x0,/* MMSYS_CG_CON1 */
	0x140001A0, 0xFFFFFFFF, 0x0,/* MMSYS_CG_CON2 */
	0x15020000, 0x1007, 0x1007,/* IMG_CG_CON */
	0x15820000, 0x11C3, 0x11C3,/* IMG_CG_CON */
	0x1602F000, 0x1, 0x1,/* VDEC_CKEN_SET */
	0x1602F004, 0x1, 0x0,/* VDEC_CKEN_CLR */
	0x1602F008, 0x1, 0x1,/* LARB_CKEN_CON_SET */
	0x1602F00C, 0x1, 0x0,/* LARB_CKEN_CON_CLR */
	0x1602F200, 0x1, 0x1,/* LAT_CKEN_SET */
	0x1602F204, 0x1, 0x0,/* LAT_CKEN_CLR */
	0x17000000, 0x10000111, 0x0,/* VENCSYS_CG_CON */
	0x17000004, 0x10000111, 0x0,/* VENCSYS_CG_SET */
	0x17000008, 0x10000111, 0x10000111,/* VENCSYS_CG_CLR */
	0x19020000, 0x7FFFE, 0x7FFFE,/* APU_CONN_CG_CON */
	0x19024000, 0x37, 0x37,/* APU_CONN1_CG_CON */
	0x19029000, 0xF, 0xF,/* APUSYS_VCORE_CG_CON */
	0x19030100, 0x7, 0x7,/* CORE_CG_CON */
	0x19031100, 0x7, 0x7,/* CORE_CG_CON */
	0x19034000, 0x181FFF, 0x181FFF,/* MDLA_CG_CON */
	0x1A000000, 0xFFDCF, 0xFFDCF,/* CAMSYS_CG_CON */
	0x1A04F000, 0x7, 0x7,/* CAMSYS_CG_CON */
	0x1A06F000, 0x7, 0x7,/* CAMSYS_CG_CON */
	0x1B000000, 0x17F, 0x17F,/* IMG_CG_CON */
	0x1F000100, 0xFFFFFFFF, 0x0,/* MDPSYS_CG_CON0 */
	0x1F000110, 0xFFFFFFFF, 0x0,/* MDPSYS_CG_CON1 */
	0x1F000120, 0xFFFFFFFF, 0x0,/* MDPSYS_CG_CON2 */
	0x1F000130, 0xFFFFFFFF, 0x0,/* MDPSYS_CG_CON3 */
	0x1F000140, 0xFFFFFFFF, 0x0 /* MDPSYS_CG_CON4 */
};

const unsigned int *AP_CG_Golden_Setting_tcl_gs_sodi =
		AP_CG_Golden_Setting_tcl_gs_sodi_data;

unsigned int AP_CG_Golden_Setting_tcl_gs_sodi_len = 90;
