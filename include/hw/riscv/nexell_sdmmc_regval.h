/*
 * Raspberry Pi (NEXELL) SD Host Controller
 *
 * Copyright (c) 2017 Antfield SAS
 *
 * Authors:
 *  Clement Deschamps <clement.deschamps@antfield.fr>
 *  Luc Michel <luc.michel@antfield.fr>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 */

#ifndef NEXELL_SDMMC_REGVAL_H
#define NEXELL_SDMMC_REGVAL_H

#define NX_SDXC_CTRL_USEINDMAC 			(1U << 25)
#define NX_SDXC_CTRL_READWAIT	 		(1U <<  6)
#define NX_SDXC_CTRL_DMAMODE_EN			(1U <<  5)
#define NX_SDXC_CTRL_DMARST			(1U <<  2)
#define NX_SDXC_CTRL_FIFORST			(1U <<  1)
#define NX_SDXC_CTRL_CTRLRST			(1U <<  0)

/*--------------------------------------------------------------------*/
#define NX_SDXC_CLKENA_LOWPWR			(1U << 16)
#define NX_SDXC_CLKENA_CLKENB			(1U <<  0)

/*--------------------------------------------------------------------*/
#define NX_SDXC_STATUS_FIFOCOUNT		(0x1FFFU << 17)
#define NX_SDXC_STATUS_FSMBUSY			(1U << 10)
#define NX_SDXC_STATUS_DATABUSY			(1U <<  9)
#define NX_SDXC_STATUS_FIFOFULL			(1U <<  3)
#define NX_SDXC_STATUS_FIFOEMPTY		(1U <<  2)

/*--------------------------------------------------------------------*/
#define NX_SDXC_CMDFLAG_STARTCMD		(1U << 31)
#define NX_SDXC_CMDFLAG_USE_HOLD_REG		(1U << 29)
#define NX_SDXC_CMDFLAG_VOLT_SWITCH		(1U << 28)
#define NX_SDXC_CMDFLAG_BOOT_MODE		(1U << 27)
#define NX_SDXC_CMDFLAG_DISABLE_BOOT		(1U << 26)
#define NX_SDXC_CMDFLAG_EXPECTBOOTACK		(1U << 25)
#define NX_SDXC_CMDFLAG_ENABLE_BOOT		(1U << 24)
#define NX_SDXC_CMDFLAG_CCS_EXPECTED		(1U << 23)
#define NX_SDXC_CMDFLAG_READCEATADEVICE		(1U << 22)
#define NX_SDXC_CMDFLAG_UPDATECLKONLY		(1U << 21)
#define NX_SDXC_CMDFLAG_SENDINIT		(1U << 15)
#define NX_SDXC_CMDFLAG_STOPABORT		(1U << 14)
#define NX_SDXC_CMDFLAG_WAITPRVDAT		(1U << 13)
#define NX_SDXC_CMDFLAG_SENDAUTOSTOP		(1U << 12)
#define NX_SDXC_CMDFLAG_BLOCK			(0U << 11)
#define NX_SDXC_CMDFLAG_STREAM			(1U << 11)
#define NX_SDXC_CMDFLAG_TXDATA			(3U <<  9)
#define NX_SDXC_CMDFLAG_RXDATA			(1U <<  9)
#define NX_SDXC_CMDFLAG_CHKRSPCRC		(1U <<  8)
#define NX_SDXC_CMDFLAG_SHORTRSP		(1U <<  6)
#define NX_SDXC_CMDFLAG_LONGRSP			(3U <<  6)

/*--------------------------------------------------------------------*/
#define NX_SDXC_RINTSTS_SDIO			(1U << 16)
#define NX_SDXC_RINTSTS_EBE			(1U << 15)
#define NX_SDXC_RINTSTS_ACD			(1U << 14)
#define NX_SDXC_RINTSTS_SBE			(1U << 13)
#define NX_SDXC_RINTSTS_HLE			(1U << 12)
#define NX_SDXC_RINTSTS_FRUN			(1U << 11)
#define NX_SDXC_RINTSTS_HTO			(1U << 10)
#define NX_SDXC_RINTSTS_DRTO			(1U <<  9)
#define NX_SDXC_RINTSTS_RTO			(1U <<  8)
#define NX_SDXC_RINTSTS_DCRC			(1U <<  7)
#define NX_SDXC_RINTSTS_RCRC			(1U <<  6)
#define NX_SDXC_RINTSTS_RXDR			(1U <<  5)
#define NX_SDXC_RINTSTS_TXDR			(1U <<  4)
#define NX_SDXC_RINTSTS_DTO			(1U <<  3)
#define NX_SDXC_RINTSTS_CD			(1U <<  2)
#define NX_SDXC_RINTSTS_RE			(1U <<  1)

#endif
