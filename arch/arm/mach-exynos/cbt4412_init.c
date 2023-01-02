// SPDX-License-Identifier: GPL-2.0+
/*
 * 
 */

#include <common.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <asm/arch/cpu.h>
#include <asm/arch/mmc.h>
#include <asm/arch/periph.h>
#include <asm/arch/pinmux.h>
#include <usb.h>
#include <net.h>
#include <mach/cpu.h>
#include <../../../drivers/net/dm9000x.h>

static void dm9000aep_pre_init(void);
static int cbt4412_init(void);
static void exynos_config_sromc(u32 srom_bank, u32 srom_bw_conf, u32 srom_bc_conf);

/* DM9000 Config */
#ifdef CONFIG_CMD_NET
#undef CONFIG_NET

#define CONFIG_DRIVER_DM9000	1
#define CONFIG_DM9000_BASE	0x05000000 		
#define DM9000_IO		CONFIG_DM9000_BASE	/* #undef CONFIG_DM_ETH */
#define DM9000_DATA		(CONFIG_DM9000_BASE + 4)/*  */
#define CONFIG_DM9000_USE_16BIT				/*  */
#define CONFIG_DM9000_NO_SROM	1			/*  */
#define CONFIG_ETHADDR		11:22:33:44:55:66
#define CONFIG_IPADDR		192.168.6.187
#define CONFIG_SERVERIP		192.168.6.186
#define CONFIG_GATEWAYIP	192.168.6.1
#define CONFIG_NETMASK		255.255.255.0

#define EXYNOS4412_SROMC_BASE 	0X12570000

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

static int cbt4412_init(void)
{

	gd->bd->bi_boot_params = (PHYS_SDRAM_1 + 0x100UL);

#ifdef CONFIG_DRIVER_DM9000
	dm9000aep_pre_init();
#endif
	return 0;
}
#endif

static void dm9000aep_pre_init(void)
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
/*
 *  exynos_config_sromc() - select the proper SROMC Bank and configure the
 *  band width control and bank control registers
 *  srom_bank    - SROM
 *  srom_bw_conf  - SMC Band witdh reg configuration value
 *  srom_bc_conf  - SMC Bank Control reg configuration value
 */

static void exynos_config_sromc(u32 srom_bank, u32 srom_bw_conf, u32 srom_bc_conf)
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


