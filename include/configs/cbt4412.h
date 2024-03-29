/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2011 Samsung Electronics
 *
 * Configuration settings for the SAMSUNG CBT4412 (EXYNOS4210) board.
 */

#ifndef __CONFIG_CBT4412_H
#define __CONFIG_CBT4412_H

#include <configs/exynos4-common.h>

/* DM9000 Config */
#ifdef CONFIG_CMD_NET
/* #define CONFIG_DRIVER_DM9000 y */
#define CONFIG_DM9000_BASE	0x05000000 		
#define DM9000_IO		CONFIG_DM9000_BASE	/*  */
#define DM9000_DATA		(CONFIG_DM9000_BASE + 4)/*  */
#define CONFIG_DM9000_USE_16BIT				/*  */
#define CONFIG_DM9000_NO_SROM	1			/*  */
#define CONFIG_ETHADDR		00:0c:29:d3:fe:1d	/*  */
#define CONFIG_IPADDR		192.168.1.230
#define CONFIG_SERVERIP		192.168.1.7
#define CONFIG_GATEWAYIP	192.168.1.1
#define CONFIG_NETMASK		255.255.255.0

#define EXYNOS4412_SROMC_BASE 	0X12570000
#endif

/*#undef CONFIG_SKIP_LOWLEVEL_INIT
#undef CONFIG_SKIP_LOWLEVEL_INIT_ONLY
*/

/* High Level Configuration Options */
#define CONFIG_EXYNOS4412		1	/* which is a EXYNOS4412 SoC */
#define CONFIG_CBT4412			1	/* working with CBT4412*/

/* CBT4412 has 4 bank of DRAM */
#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define PHYS_SDRAM_1			CONFIG_SYS_SDRAM_BASE
#define SDRAM_BANK_SIZE			(256 << 20)	/* 256 MB */

/* memtest works on */
/* #define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x3E00000) */

#define CONFIG_MACH_TYPE		MACH_TYPE_EXYNOS4412

/* select serial console configuration */

/* Console configuration */
#define CONFIG_DEFAULT_CONSOLE		"console=ttySAC0,115200n8\0"


#define CONFIG_SYS_MEM_TOP_HIDE	(1 << 20)	/* ram console */

#define CONFIG_SYS_MONITOR_BASE	0x00000000

/* Power Down Modes */
#define S5P_CHECK_SLEEP			0x00000BAD
#define S5P_CHECK_DIDLE			0xBAD00000
#define S5P_CHECK_LPA			0xABAD0000

/* MMC SPL */
#define COPY_BL2_FNPTR_ADDR	0x02020030

#define CONFIG_EXTRA_ENV_SETTINGS \
		"initrd_high=0xffffffff\0" \
		"loadaddr=0x40008000\0" \
	"rdaddr=0x43000000\0" \
	"kerneladdr=0x40008000\0" \
	"ramdiskaddr=0x43000000\0" \
	"console=ttySAC0,115200n8\0" \
	"mmcdev=0\0" \
	"bootenv=uEnv.txt\0" \
	"loadbootenv=load mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc ...; " \
		"env import -t $loadaddr $filesize\0" \
        "loadbootscript=load mmc ${mmcdev} ${loadaddr} boot.scr\0" \
        "bootscript=echo Running bootscript from mmc${mmcdev} ...; " \
                "source ${loadaddr}\0"
#define CONFIG_BOOTCOMMAND \
	"bootm ${loadaddr} "

#define CONFIG_CLK_1000_400_200

/* MIU (Memory Interleaving Unit) */
#define CONFIG_MIU_2BIT_21_7_INTERLEAVED

#define RESERVE_BLOCK_SIZE		(512)
#define BL1_SIZE			(8 << 10) /*8 K reserved for BL1*/
#define BL2_SIZE			(16 << 10) /*16 K reserved for BL2*/

#define CONFIG_SPL_MAX_FOOTPRINT	(14 * 1024)

#define CONFIG_SYS_INIT_SP_ADDR		0x02040000

/* U-Boot copy size from boot Media to DRAM.*/
#define COPY_UBOOT_SIZE		0xC8000 //800KB
#define UBOOT_START_OFFSET	((RESERVE_BLOCK_SIZE + BL1_SIZE + BL2_SIZE) /512)
#define UBOOT_SIZE_BLOC_COUNT	(COPY_UBOOT_SIZE /512)

#define COPY_BL2_SIZE		0x4000
#define BL2_START_OFFSET	((RESERVE_BLOCK_SIZE + BL1_SIZE) /512)
#define BL2_SIZE_BLOC_COUNT	(COPY_BL2_SIZE /512)

#endif	/* __CONFIG_H */
