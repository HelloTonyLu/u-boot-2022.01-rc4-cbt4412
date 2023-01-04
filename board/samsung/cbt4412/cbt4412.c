// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2011 Samsung Electronics
 */

#include <common.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <asm/arch/cpu.h>
#include <asm/arch/mmc.h>
#include <asm/arch/periph.h>
#include <asm/arch/pinmux.h>
#include <usb.h>
#include <asm/system.h>
#include <init.h>
#include <command.h>
#include <net.h>
#include <linux/delay.h>
#include <netdev.h>
#include <debug_uart.h>
#include "configs/cbt4412.h"

/* DM9000 Config */
#ifdef CONFIG_CMD_NET

#define DM9000_Tacs     (0x1)   // address set-up
#define DM9000_Tcos     (0x1)   // chip selection set-up
#define DM9000_Tacc     (0x5)   // access cycle
#define DM9000_Tcoh     (0x1)   // chip selection hold
#define DM9000_Tah      (0xC)   // address holding time
#define DM9000_Tacp     (0x9)   // page mode access cycle
#define DM9000_PMC      (0x1)   // normal(1data)page mode configuration

#endif

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_TARGET_CBT4412
struct exynos_sromc {
	unsigned int bw;
	unsigned int bc[6];
};

#ifdef CONFIG_CMD_NET 

/*
 *  exynos_config_sromc() - select the proper SROMC Bank and configure the
 *  band width control and bank control registers
 *  srom_bank    - SROM
 *  srom_bw_conf  - SMC Band witdh reg configuration value
 *  srom_bc_conf  - SMC Bank Control reg configuration value
 */

void exynos_config_sromc(u32 srom_bank, u32 srom_bw_conf, u32 srom_bc_conf)
{
	unsigned int tmp;
	struct exynos_sromc *srom = (struct exynos_sromc *)(EXYNOS4412_SROMC_BASE);

	/* Configure SMC_BW register to handle proper SROMC
	 * bank */
	tmp = srom->bw;
	tmp &= ~(0xF << (srom_bank * 4));
	tmp |= srom_bw_conf;
	srom->bw = tmp;

	/* Configure SMC_BC
	 * register */
	srom->bc[srom_bank] = srom_bc_conf;
}

void dm9000aep_pre_init(void)
{
	unsigned char smc_bank_num = 1;
	unsigned int     smc_bw_conf=0;
	unsigned int     smc_bc_conf=0;

	/* gpio configuration */
	writel(0x00220020, 0x11000000 + 0x120);//GPY0CON
	writel(0x00002222, 0x11000000 + 0x140);//GPY1CON
	/* 16 Bit bus width */
	writel(0x22222222, 0x11000000 + 0x180);//GPY3CON
	writel(0x0000FFFF, 0x11000000 + 0x188);//GPY3PUD
	writel(0x22222222, 0x11000000 + 0x1C0);//GPY5CON
	writel(0x0000FFFF, 0x11000000 + 0x1C8);//GPY5PUD
	writel(0x22222222, 0x11000000 + 0x1E0);//GPY6CON
	writel(0x0000FFFF, 0x11000000 + 0x1E8);//GPY6PUD
	              
	smc_bw_conf &= ~(0xf<<4);
	smc_bw_conf |= (1<<7) | (1<<6) | (1<<5) | (1<<4);
	smc_bc_conf = ((DM9000_Tacs << 28)
			| (DM9000_Tcos << 24)
			| (DM9000_Tacc << 16)
			| (DM9000_Tcoh << 12)
			| (DM9000_Tah << 8)
			| (DM9000_Tacp << 4)
			| (DM9000_PMC));
	exynos_config_sromc(smc_bank_num,smc_bw_conf,smc_bc_conf);
}

int board_eth_init(struct bd_info *bis)
{	
	int rc = 0; 
#ifdef CONFIG_DRIVER_DM9000
	dm9000aep_pre_init();
	rc = dm9000_initialize(bis);
	printascii("dm9000_initialize(bis) was runned\r\n");
#endif

#if defined(CONFIG_RESET_PHY_R)
	printascii("Reset Ethernet PHY\r\n");
	reset_phy();
#endif
	return rc;                                                               
}   
#endif 

#endif /* end of target_4412*/

int exynos_init(void)
{
	return 0;
}

int board_usb_init(int index, enum usb_init_type init)
{
	return 0;
}

#ifdef CONFIG_BOARD_EARLY_INIT_F
int exynos_early_init_f(void)
{
	return 0;
}
#endif


