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

#ifndef NEXELL_SDMMC_H
#define NEXELL_SDMMC_H

#include "hw/sysbus.h"
#include "hw/sd/sd.h"

#define TYPE_NEXELL_SDMMC "riscv.nexell.sdmmc"
#define NEXELL_SDMMC(obj) \
        OBJECT_CHECK(NexellSDMMCState, (obj), TYPE_NEXELL_SDMMC)

#define NEXELL_SDMMC_FIFO_LEN 16
#define NEXELL_SWALLOW_NUM_SDMMC 2

typedef struct NexellSDMMCState
{
    unsigned int CTRL;			// 0x000 : Control
    unsigned int PWREN;			// 0x004 : Power Enable
    unsigned int CLKDIV;		// 0x008 : Clock Divider
    unsigned int CLKSRC;		// 0x00C : Clock Source
    unsigned int CLKENA;		// 0x010 : Clock Enable
    unsigned int TMOUT;			// 0x014 : Time-Out
    unsigned int CTYPE;			// 0x018 : Card Type
    unsigned int BLKSIZ;		// 0x01C : Block Size
    unsigned int BYTCNT;		// 0x020 : Byte Count
    unsigned int INTMASK;		// 0x024 : Interrupt Mask
    unsigned int CMDARG;		// 0x028 : Command Argument
    unsigned int CMD;			// 0x02C : Command
    unsigned int RESP[4];		// 0x030 : Response 0
    unsigned int MINTSTS;		// 0x040 : Masked Interrupt Status
    unsigned int RINTSTS;		// 0x044 : Raw Interrupt Status
    unsigned int STATUS;		// 0x048 : Status - Mainly for Debug Purpose
    unsigned int FIFOTH;		// 0x04C : FIFO Threshold
    unsigned int CDETECT;		// 0x050 : Card Detect
    unsigned int WRTPRT;		// 0x054 : Write Protect
    unsigned int GPIO;			// 0x058 : General Purpose Input/Output
    unsigned int TCBCNT;		// 0x05C : Transferred CIU card byte count
    unsigned int TBBCNT;		// 0x060 : Transferred Host Byte Count
    unsigned int DEBNCE;		// 0x064 : Card Detect Debounce
    unsigned int USRID;			// 0x068 : User ID
    unsigned int VERID;			// 0x06C : Version ID
    unsigned int HCON;			// 0x070 : Hardware Configuration
    unsigned int UHS_REG;		// 0x074 : UHS_REG register
    unsigned int RSTn;			// 0x078 : Hardware reset register
    unsigned int _Rev0;			// 0x07C
    unsigned int BMOD;			// 0x080 : Bus Mode
    unsigned int PLDMND;		// 0x084 : Poll Demand
    unsigned int DBADDR;		// 0x088 : Descriptor List Base Address
    unsigned int IDSTS;			// 0x08C : Internal DMAC Status
    unsigned int IDINTEN;		// 0x090 : Internal DMAC Interrupt Enable
    unsigned int DSCADDR;		// 0x094 : Current Host Descriptor Address
    unsigned int BUFADDR;		// 0x098 : Current Buffer Descriptor Address
    unsigned char  _Rev1[0x100-0x09C];	// 0x09C ~ 0x100 reserved area
    unsigned int CARDTHRCTL;		// 0x100 : Card Read Threshold Enable
    unsigned int BACKEND_POWER;		// 0x104 : Back-end Power
    unsigned int UHS_REG_EXT;		// 0x108 : eMMC 4.5 1.2V
    unsigned int EMMC_DDR_REG;		// 0x10C : eMMC DDR START bit detection control
    unsigned int ENABLE_SHIFT;		// 0x110 : Phase shift control
    unsigned int CLKCTRL;		// 0x114 : External clock phase & delay control
    unsigned char  _Rev2[0x200-0x118];	// 0x118 ~ 0x200
    unsigned int DATA;			// 0x200 : Data
    unsigned char  _Rev3[0x400-0x204];	// 0x204 ~ 0x400
    unsigned int TIEMODE;		// 0x400
    unsigned int TIESRAM;		// 0x404
    unsigned int TIEDRVPHASE;		// 0x408
    unsigned int TIESMPPHASE;		// 0x40C
    unsigned int TIEDSDELAY;		// 0x410

  SysBusDevice busdev;
  SDBus sdbus;
  MemoryRegion mmio;

  qemu_irq irq;
} NexellSDMMCState;

enum {
    NEXELL_SDMMC__CTRL,                   
    NEXELL_SDMMC__PWREN,                  
    NEXELL_SDMMC__CLKDIV,                 
    NEXELL_SDMMC__CLKSRC,                 
    NEXELL_SDMMC__CLKENA,                 
    NEXELL_SDMMC__TMOUT,                  
    NEXELL_SDMMC__CTYPE,                  
    NEXELL_SDMMC__BLKSIZ,                 
    NEXELL_SDMMC__BYTCNT,                 
    NEXELL_SDMMC__INTMASK,                
    NEXELL_SDMMC__CMDARG,                 
    NEXELL_SDMMC__CMD,                    
    NEXELL_SDMMC__RESP,
    NEXELL_SDMMC__MINTSTS,                
    NEXELL_SDMMC__RINTSTS,                
    NEXELL_SDMMC__STATUS,                 
    NEXELL_SDMMC__FIFOTH,                 
    NEXELL_SDMMC__CDETECT,                
    NEXELL_SDMMC__WRTPRT,                 
    NEXELL_SDMMC__GPIO,                   
    NEXELL_SDMMC__TCBCNT,                 
    NEXELL_SDMMC__TBBCNT,                 
    NEXELL_SDMMC__DEBNCE,                 
    NEXELL_SDMMC__USRID,                  
    NEXELL_SDMMC__VERID,                  
    NEXELL_SDMMC__HCON,                   
    NEXELL_SDMMC__UHS_REG,                
    NEXELL_SDMMC__RSTn,                   
    NEXELL_SDMMC___Rev0,                  
    NEXELL_SDMMC__BMOD,                   
    NEXELL_SDMMC__PLDMND,                 
    NEXELL_SDMMC__DBADDR,                
    NEXELL_SDMMC__IDSTS,                 
    NEXELL_SDMMC__IDINTEN,               
    NEXELL_SDMMC__DSCADDR,               
    NEXELL_SDMMC__BUFADDR,               
    NEXELL_SDMMC___Rev1,
    NEXELL_SDMMC__CARDTHRCTL,            
    NEXELL_SDMMC__BACKEND_POWER,         
    NEXELL_SDMMC__UHS_REG_EXT,           
    NEXELL_SDMMC__EMMC_DDR_REG,          
    NEXELL_SDMMC__ENABLE_SHIFT,          
    NEXELL_SDMMC__CLKCTRL,               
    NEXELL_SDMMC___Rev2,
    NEXELL_SDMMC__DATA,                  
    NEXELL_SDMMC___Rev3,
    NEXELL_SDMMC__TIEMODE,               
    NEXELL_SDMMC__TIESRAM,               
    NEXELL_SDMMC__TIEDRVPHASE,           
    NEXELL_SDMMC__TIESMPPHASE,           
    NEXELL_SDMMC__TIEDSDELAY,            
    NEXELL_SDMMC_ENUM_MAX,
};

#define   NEXELL_SDMMC_OFFSET_CTRL              0x000 
#define   NEXELL_SDMMC_OFFSET_PWREN             0x004 
#define   NEXELL_SDMMC_OFFSET_CLKDIV            0x008 
#define   NEXELL_SDMMC_OFFSET_CLKSRC            0x00C 
#define   NEXELL_SDMMC_OFFSET_CLKENA            0x010 
#define   NEXELL_SDMMC_OFFSET_TMOUT             0x014 
#define   NEXELL_SDMMC_OFFSET_CTYPE             0x018 
#define   NEXELL_SDMMC_OFFSET_BLKSIZ            0x01C 
#define   NEXELL_SDMMC_OFFSET_BYTCNT            0x020 
#define   NEXELL_SDMMC_OFFSET_INTMASK           0x024 
#define   NEXELL_SDMMC_OFFSET_CMDARG            0x028 
#define   NEXELL_SDMMC_OFFSET_CMD               0x02C 
#define   NEXELL_SDMMC_OFFSET_RESP              0x030
#define   NEXELL_SDMMC_OFFSET_MINTSTS           0x040 
#define   NEXELL_SDMMC_OFFSET_RINTSTS           0x044 
#define   NEXELL_SDMMC_OFFSET_STATUS            0x048 
#define   NEXELL_SDMMC_OFFSET_FIFOTH            0x04C 
#define   NEXELL_SDMMC_OFFSET_CDETECT           0x050 
#define   NEXELL_SDMMC_OFFSET_WRTPRT            0x054 
#define   NEXELL_SDMMC_OFFSET_GPIO              0x058 
#define   NEXELL_SDMMC_OFFSET_TCBCNT            0x05C 
#define   NEXELL_SDMMC_OFFSET_TBBCNT            0x060 
#define   NEXELL_SDMMC_OFFSET_DEBNCE            0x064 
#define   NEXELL_SDMMC_OFFSET_USRID             0x068 
#define   NEXELL_SDMMC_OFFSET_VERID             0x06C 
#define   NEXELL_SDMMC_OFFSET_HCON              0x070 
#define   NEXELL_SDMMC_OFFSET_UHS_REG           0x074 
#define   NEXELL_SDMMC_OFFSET_RSTn              0x078 
#define   NEXELL_SDMMC_OFFSET__Rev0             0x07C 
#define   NEXELL_SDMMC_OFFSET_BMOD              0x080 
#define   NEXELL_SDMMC_OFFSET_PLDMND            0x084 
#define   NEXELL_SDMMC_OFFSET_DBADDR            0x088
#define   NEXELL_SDMMC_OFFSET_IDSTS             0x08C
#define   NEXELL_SDMMC_OFFSET_IDINTEN           0x090
#define   NEXELL_SDMMC_OFFSET_DSCADDR           0x094
#define   NEXELL_SDMMC_OFFSET_BUFADDR           0x098
#define   NEXELL_SDMMC_OFFSET__Rev1             0x09C
#define   NEXELL_SDMMC_OFFSET_CARDTHRCTL        0x100
#define   NEXELL_SDMMC_OFFSET_BACKEND_POWER     0x104
#define   NEXELL_SDMMC_OFFSET_UHS_REG_EXT       0x108
#define   NEXELL_SDMMC_OFFSET_EMMC_DDR_REG      0x10C
#define   NEXELL_SDMMC_OFFSET_ENABLE_SHIFT      0x110
#define   NEXELL_SDMMC_OFFSET_CLKCTRL           0x114
#define   NEXELL_SDMMC_OFFSET__Rev2             0x118
#define   NEXELL_SDMMC_OFFSET_DATA              0x200
#define   NEXELL_SDMMC_OFFSET__Rev3             0x204
#define   NEXELL_SDMMC_OFFSET_TIEMODE           0x400
#define   NEXELL_SDMMC_OFFSET_TIESRAM           0x404
#define   NEXELL_SDMMC_OFFSET_TIEDRVPHASE       0x408
#define   NEXELL_SDMMC_OFFSET_TIESMPPHASE       0x40C
#define   NEXELL_SDMMC_OFFSET_TIEDSDELAY        0x410


NexellSDMMCState *nexell_sdmmc_create(MemoryRegion *address_space, hwaddr base, qemu_irq irq);

#endif
