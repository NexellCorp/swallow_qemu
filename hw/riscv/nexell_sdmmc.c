/*
 * QEMU model of the SDMMC on the SiFive E300 and U500 series SOCs.
 *
 * Copyright (c) 2016 Stefan O'Rear
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2 or later, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include "chardev/char.h"
#include "chardev/char-fe.h"
#include "target/riscv/cpu.h"
#include "hw/riscv/nexell_sdmmc.h"
#include "hw/riscv/nexell_sdmmc_regval.h"

#define TYPE_READ  "sdmmc_read"
#define TYPE_WRITE "sdmmc_write"

static void sdmmc_register_detail(const char* type, void *opaque, hwaddr offset);

/* static const struct sdmmcMapEntry { */
/*     hwaddr offset; */
/*     char   name[32]; */
/* } nx_sdmmc_regmap[] = { */
/*     [NEXELL_SDMMC__CTRL]         = {0x000, "CTRL"}, */
/*     [NEXELL_SDMMC__PWREN]        = {0x004, "PWREN"}, */
/*     [NEXELL_SDMMC__CLKDIV]       = {0x008, "CLKDIV"}, */
/*     [NEXELL_SDMMC__CLKSRC]       = {0x00C, "CLKSRC"}, */
/*     [NEXELL_SDMMC__CLKENA]       = {0x010, "CLKENA"}, */
/*     [NEXELL_SDMMC__TMOUT]        = {0x014, "TMOUT"}, */
/*     [NEXELL_SDMMC__CTYPE]        = {0x018, "CTYPE"}, */
/*     [NEXELL_SDMMC__BLKSIZ]       = {0x01C, "BLKSIZ"}, */
/*     [NEXELL_SDMMC__BYTCNT]       = {0x020, "BYTCNT"}, */
/*     [NEXELL_SDMMC__INTMASK]      = {0x024, "INTMASK"}, */
/*     [NEXELL_SDMMC__CMDARG]       = {0x028, "CMDARG"}, */
/*     [NEXELL_SDMMC__CMD]          = {0x02C, "CMD"}, */
/*     [NEXELL_SDMMC__RESP]         = {0x030, "RESP"}, */
/*     [NEXELL_SDMMC__MINTSTS]      = {0x040, "MINTSTS"}, */
/*     [NEXELL_SDMMC__RINTSTS]      = {0x044, "RINTSTS"}, */
/*     [NEXELL_SDMMC__STATUS]       = {0x048, "STATUS"}, */
/*     [NEXELL_SDMMC__FIFOTH]       = {0x04C, "FIFOTH"}, */
/*     [NEXELL_SDMMC__CDETECT]      = {0x050, "CDETECT"}, */
/*     [NEXELL_SDMMC__WRTPRT]       = {0x054, "WRTPRT"}, */
/*     [NEXELL_SDMMC__GPIO]         = {0x058, "GPIO"}, */
/*     [NEXELL_SDMMC__TCBCNT]       = {0x05C, "TCBCNT"}, */
/*     [NEXELL_SDMMC__TBBCNT]       = {0x060, "TBBCNT"}, */
/*     [NEXELL_SDMMC__DEBNCE]       = {0x064, "DEBNCE"}, */
/*     [NEXELL_SDMMC__USRID]        = {0x068, "USRID"}, */
/*     [NEXELL_SDMMC__VERID]        = {0x06C, "VERID"}, */
/*     [NEXELL_SDMMC__HCON]         = {0x070, "HCON"}, */
/*     [NEXELL_SDMMC__UHS_REG]      = {0x074, "UHS_REG"}, */
/*     [NEXELL_SDMMC__RSTn]         = {0x078, "RSTn"}, */
/*     [NEXELL_SDMMC___Rev0]        = {0x07C, "_Rev0"}, */
/*     [NEXELL_SDMMC__BMOD]         = {0x080, "BMOD"}, */
/*     [NEXELL_SDMMC__PLDMND]       = {0x084, "PLDMND"}, */
/*     [NEXELL_SDMMC__DBADDR]       = {0x088, "DBADDR"}, */
/*     [NEXELL_SDMMC__IDSTS]        = {0x08C, "IDSTS"}, */
/*     [NEXELL_SDMMC__IDINTEN]      = {0x090, "IDINTEN"}, */
/*     [NEXELL_SDMMC__DSCADDR]      = {0x094, "DSCADDR"}, */
/*     [NEXELL_SDMMC__BUFADDR]      = {0x098, "BUFADDR"}, */
/*     [NEXELL_SDMMC___Rev1]        = {0x09C, "_Rev1"}, */
/*     [NEXELL_SDMMC__CARDTHRCTL]   = {0x100, "CARDTHRCTL"}, */
/*     [NEXELL_SDMMC__BACKEND_POWER]= {0x104, "BACKEND_POWER"}, */
/*     [NEXELL_SDMMC__UHS_REG_EXT]  = {0x108, "UHS_REG_EXT"}, */
/*     [NEXELL_SDMMC__EMMC_DDR_REG] = {0x10C, "EMMC_DDR_REG"}, */
/*     [NEXELL_SDMMC__ENABLE_SHIFT] = {0x110, "ENABLE_SHIFT"}, */
/*     [NEXELL_SDMMC__CLKCTRL]      = {0x114, "CLKCTRL"}, */
/*     [NEXELL_SDMMC___Rev2]        = {0x118, "_Rev2"}, */
/*     [NEXELL_SDMMC__DATA]         = {0x200, "DATA"}, */
/*     [NEXELL_SDMMC___Rev3]        = {0x204, "_Rev3"}, */
/*     [NEXELL_SDMMC__TIEMODE]      = {0x400, "TIEMODE"}, */
/*     [NEXELL_SDMMC__TIESRAM]      = {0x404, "TIESRAM"}, */
/*     [NEXELL_SDMMC__TIEDRVPHASE]  = {0x408, "TIEDRVPHASE"}, */
/*     [NEXELL_SDMMC__TIESMPPHASE]  = {0x40C, "TIESMPPHASE"}, */
/*     [NEXELL_SDMMC__TIEDSDELAY]   = {0x410, "TIEDSDELAY"}, */
/* }; */

/* static void update_irq(NexellSDMMCState *s) */
/* { */
/*     /\* int cond = 0; *\/ */
/*     /\* if ((s->ie & NEXELL_SDMMC_IE_RXWM) && s->rx_fifo_len) { *\/ */
/*     /\*     cond = 1; *\/ */
/*     /\* } *\/ */
/*     /\* if (cond) { *\/ */
/*     /\*     qemu_irq_raise(s->irq); *\/ */
/*     /\* } else { *\/ */
/*     /\*     qemu_irq_lower(s->irq); *\/ */
/*     /\* } *\/ */
/*     printf("[QEMU] %s \n", __func__);     */
/* } */

static uint64_t sdmmc_read(void *opaque, hwaddr offset, unsigned int size)
{
    NexellSDMMCState *s = opaque;
//    int cnt = NEXELL_SDMMC_ENUM_MAX;
    uint64_t temp = 0;

    /* do { */
    /*     if (nx_sdmmc_regmap[cnt-1].offset == offset) { */
    /*         printf("[QEMU][%s] %s: offset=0x%lx, ",   \ */
    /*                __func__, \ */
    /*                nx_sdmmc_regmap[cnt-1].name, \ */
    /*                offset); */
    /*         break; */
    /*     } */
    /*     else */
    /*         cnt -= 1; */
    /* } while(cnt > 0); */

    switch (offset) {
    case NEXELL_SDMMC_OFFSET_CTRL         :  temp = s->CTRL;               break;
    case NEXELL_SDMMC_OFFSET_PWREN        :  temp = s->PWREN;              break; 
    case NEXELL_SDMMC_OFFSET_CLKDIV       :  temp = s->CLKDIV;             break;
    case NEXELL_SDMMC_OFFSET_CLKSRC       :  temp = s->CLKSRC;             break;  
    case NEXELL_SDMMC_OFFSET_CLKENA       :  temp = s->CLKENA;             break; 
    case NEXELL_SDMMC_OFFSET_TMOUT        :  temp = s->TMOUT;              break;       
    case NEXELL_SDMMC_OFFSET_CTYPE        :  temp = s->CTYPE;              break;    
    case NEXELL_SDMMC_OFFSET_BLKSIZ       :  temp = s->BLKSIZ;             break;    
    case NEXELL_SDMMC_OFFSET_BYTCNT       :  temp = s->BYTCNT;             break;    
    case NEXELL_SDMMC_OFFSET_INTMASK      :  temp = s->INTMASK;            break;    
    case NEXELL_SDMMC_OFFSET_CMDARG       :  temp = s->CMDARG;             break;  
    case NEXELL_SDMMC_OFFSET_CMD          :  temp = s->CMD;                break;  
    case NEXELL_SDMMC_OFFSET_RESP         :  temp = s->RESP[0];            break;
    case NEXELL_SDMMC_OFFSET_MINTSTS      :  temp = s->MINTSTS;            break;  
    case NEXELL_SDMMC_OFFSET_RINTSTS      :  temp = s->RINTSTS;            break; 
    case NEXELL_SDMMC_OFFSET_STATUS       :  temp = s->STATUS;             break;  
    case NEXELL_SDMMC_OFFSET_FIFOTH       :  temp = s->FIFOTH;             break;  
    case NEXELL_SDMMC_OFFSET_CDETECT      :  temp = s->CDETECT;            break; 
    case NEXELL_SDMMC_OFFSET_WRTPRT       :  temp = s->WRTPRT;             break;    
    case NEXELL_SDMMC_OFFSET_GPIO         :  temp = s->GPIO;               break;     
    case NEXELL_SDMMC_OFFSET_TCBCNT       :  temp = s->TCBCNT;             break;      
    case NEXELL_SDMMC_OFFSET_TBBCNT       :  temp = s->TBBCNT;             break;  
    case NEXELL_SDMMC_OFFSET_DEBNCE       :  temp = s->DEBNCE;             break;   
    case NEXELL_SDMMC_OFFSET_USRID        :  temp = s->USRID;              break;
    case NEXELL_SDMMC_OFFSET_VERID        :  temp = s->VERID;              break; 
    case NEXELL_SDMMC_OFFSET_HCON         :  temp = s->HCON;               break;       
    case NEXELL_SDMMC_OFFSET_UHS_REG      :  temp = s->UHS_REG;            break;          
    case NEXELL_SDMMC_OFFSET_RSTn         :  temp = s->RSTn;               break;       
    case NEXELL_SDMMC_OFFSET__Rev0        :  temp = s->_Rev0;              break;       
    case NEXELL_SDMMC_OFFSET_BMOD         :  temp = s->BMOD;               break;  
    case NEXELL_SDMMC_OFFSET_PLDMND       :  temp = s->PLDMND;             break;  
    case NEXELL_SDMMC_OFFSET_DBADDR       :  temp = s->DBADDR;             break;
    case NEXELL_SDMMC_OFFSET_IDSTS        :  temp = s->IDSTS;              break;
    case NEXELL_SDMMC_OFFSET_IDINTEN      :  temp = s->IDINTEN;            break; 
    case NEXELL_SDMMC_OFFSET_DSCADDR      :  temp = s->DSCADDR;            break;
    case NEXELL_SDMMC_OFFSET_BUFADDR      :  temp = s->BUFADDR;            break;
    case NEXELL_SDMMC_OFFSET__Rev1        :  temp = s->_Rev1[0];           break;
    case NEXELL_SDMMC_OFFSET_CARDTHRCTL   :  temp = s->CARDTHRCTL;         break;
    case NEXELL_SDMMC_OFFSET_BACKEND_POWER:  temp = s->BACKEND_POWER;      break;
    case NEXELL_SDMMC_OFFSET_UHS_REG_EXT  :  temp = s->UHS_REG_EXT;        break;
    case NEXELL_SDMMC_OFFSET_EMMC_DDR_REG :  temp = s->EMMC_DDR_REG;       break;
    case NEXELL_SDMMC_OFFSET_ENABLE_SHIFT :  temp = s->ENABLE_SHIFT;       break;
    case NEXELL_SDMMC_OFFSET_CLKCTRL      :  temp = s->CLKCTRL;            break;
    case NEXELL_SDMMC_OFFSET__Rev2        :  temp = s->_Rev2[0];           break;
    case NEXELL_SDMMC_OFFSET_DATA         :  temp = s->DATA;               break;
    case NEXELL_SDMMC_OFFSET__Rev3        :  temp = s->_Rev3[0];           break;
    case NEXELL_SDMMC_OFFSET_TIEMODE      :  temp = s->TIEMODE;            break;
    case NEXELL_SDMMC_OFFSET_TIESRAM      :  temp = s->TIESRAM;            break;
    case NEXELL_SDMMC_OFFSET_TIEDRVPHASE  :  temp = s->TIEDRVPHASE;        break;
    case NEXELL_SDMMC_OFFSET_TIESMPPHASE  :  temp = s->TIESMPPHASE;        break;
    case NEXELL_SDMMC_OFFSET_TIEDSDELAY   :  temp = s->TIEDSDELAY;         break;
    }
//    printf("val=%lu \n", temp);

//    sdmmc_register_detail(TYPE_READ, opaque, offset);
    return temp;
}

static void sdmmc_write(void *opaque, hwaddr offset, uint64_t val64, unsigned int size)
{
    NexellSDMMCState *s = opaque;

    /* int cnt = NEXELL_SDMMC_ENUM_MAX; */

    /* do { */
    /*     if (nx_sdmmc_regmap[cnt-1].offset == offset) { */
    /*         printf("[QEMU][%s] %s: write to offset=0x%lx, val=0x%lx\n", \ */
    /*                __func__, \ */
    /*                nx_sdmmc_regmap[cnt-1].name, \ */
    /*                offset, */
    /*                val64); */
    /*         break; */
    /*     } */
    /*     else */
    /*         cnt -= 1; */
    /* } while(cnt > 0); */

    switch (offset) {
    case NEXELL_SDMMC_OFFSET_CTRL         :  s->CTRL = val64;                     break;
    case NEXELL_SDMMC_OFFSET_PWREN        :  s->PWREN = val64;                    break; 
    case NEXELL_SDMMC_OFFSET_CLKDIV       :  s->CLKDIV = val64;                   break;
    case NEXELL_SDMMC_OFFSET_CLKSRC       :  s->CLKSRC = val64;                   break;  
    case NEXELL_SDMMC_OFFSET_CLKENA       :  s->CLKENA = val64;                   break; 
    case NEXELL_SDMMC_OFFSET_TMOUT        :  s->TMOUT = val64;                    break;       
    case NEXELL_SDMMC_OFFSET_CTYPE        :  s->CTYPE = val64;                    break;    
    case NEXELL_SDMMC_OFFSET_BLKSIZ       :  s->BLKSIZ = val64;                   break;    
    case NEXELL_SDMMC_OFFSET_BYTCNT       :  s->BYTCNT = val64;                   break;    
    case NEXELL_SDMMC_OFFSET_INTMASK      :  s->INTMASK = val64;                  break;    
    case NEXELL_SDMMC_OFFSET_CMDARG       :  s->CMDARG = val64;                   break;  
    case NEXELL_SDMMC_OFFSET_CMD          :  s->CMD = val64;                      break;  
    case NEXELL_SDMMC_OFFSET_RESP         :  s->RESP[0] = val64;                  break;
    case NEXELL_SDMMC_OFFSET_MINTSTS      :  s->MINTSTS = val64;                  break;  
    case NEXELL_SDMMC_OFFSET_RINTSTS      :  s->RINTSTS = val64;                  break; 
    case NEXELL_SDMMC_OFFSET_STATUS       :  s->STATUS = val64;                   break;  
    case NEXELL_SDMMC_OFFSET_FIFOTH       :  s->FIFOTH = val64;                   break;  
    case NEXELL_SDMMC_OFFSET_CDETECT      :  s->CDETECT = val64;                  break; 
    case NEXELL_SDMMC_OFFSET_WRTPRT       :  s->WRTPRT = val64;                   break;    
    case NEXELL_SDMMC_OFFSET_GPIO         :  s->GPIO = val64;                     break;     
    case NEXELL_SDMMC_OFFSET_TCBCNT       :  s->TCBCNT = val64;                   break;      
    case NEXELL_SDMMC_OFFSET_TBBCNT       :  s->TBBCNT = val64;                   break;  
    case NEXELL_SDMMC_OFFSET_DEBNCE       :  s->DEBNCE = val64;                   break;   
    case NEXELL_SDMMC_OFFSET_USRID        :  s->USRID = val64;                    break;
    case NEXELL_SDMMC_OFFSET_VERID        :  s->VERID = val64;                    break; 
    case NEXELL_SDMMC_OFFSET_HCON         :  s->HCON = val64;                     break;       
    case NEXELL_SDMMC_OFFSET_UHS_REG      :  s->UHS_REG = val64;                  break;          
    case NEXELL_SDMMC_OFFSET_RSTn         :  s->RSTn = val64;                     break;       
    case NEXELL_SDMMC_OFFSET__Rev0        :  s->_Rev0 = val64;                    break;       
    case NEXELL_SDMMC_OFFSET_BMOD         :  s->BMOD = val64;                     break;  
    case NEXELL_SDMMC_OFFSET_PLDMND       :  s->PLDMND = val64;                   break;  
    case NEXELL_SDMMC_OFFSET_DBADDR       :  s->DBADDR = val64;                   break;
    case NEXELL_SDMMC_OFFSET_IDSTS        :  s->IDSTS = val64;                    break;
    case NEXELL_SDMMC_OFFSET_IDINTEN      :  s->IDINTEN = val64;                  break; 
    case NEXELL_SDMMC_OFFSET_DSCADDR      :  s->DSCADDR = val64;                  break;
    case NEXELL_SDMMC_OFFSET_BUFADDR      :  s->BUFADDR = val64;                  break;
    case NEXELL_SDMMC_OFFSET__Rev1        :  s->_Rev1[0] = val64;                 break;
    case NEXELL_SDMMC_OFFSET_CARDTHRCTL   :  s->CARDTHRCTL = val64;               break;
    case NEXELL_SDMMC_OFFSET_BACKEND_POWER:  s->BACKEND_POWER = val64;            break;
    case NEXELL_SDMMC_OFFSET_UHS_REG_EXT  :  s->UHS_REG_EXT = val64;              break;
    case NEXELL_SDMMC_OFFSET_EMMC_DDR_REG :  s->EMMC_DDR_REG = val64;             break;
    case NEXELL_SDMMC_OFFSET_ENABLE_SHIFT :  s->ENABLE_SHIFT = val64;             break;
    case NEXELL_SDMMC_OFFSET_CLKCTRL      :  s->CLKCTRL = val64;                  break;
    case NEXELL_SDMMC_OFFSET__Rev2        :  s->_Rev2[0] = val64;                 break;
    case NEXELL_SDMMC_OFFSET_DATA         :  s->DATA = val64;                     break;
    case NEXELL_SDMMC_OFFSET__Rev3        :  s->_Rev3[0] = val64;                 break;
    case NEXELL_SDMMC_OFFSET_TIEMODE      :  s->TIEMODE = val64;                  break;
    case NEXELL_SDMMC_OFFSET_TIESRAM      :  s->TIESRAM = val64;                  break;
    case NEXELL_SDMMC_OFFSET_TIEDRVPHASE  :  s->TIEDRVPHASE = val64;              break;
    case NEXELL_SDMMC_OFFSET_TIESMPPHASE  :  s->TIESMPPHASE = val64;              break;
    case NEXELL_SDMMC_OFFSET_TIEDSDELAY   :  s->TIEDSDELAY = val64;               break;
    default:
        //hw_error("[SUKER_QEMU-ERROR] %s: bad read: offset=0x%x\n", __func__, (int)offset);
        break;
    }
    sdmmc_register_detail(TYPE_WRITE, opaque, offset);
}

static void sdmmc_register_detail(const char *type, void *opaque, hwaddr offset)
{
    NexellSDMMCState *s = opaque;
    
    switch (offset) {
    case NEXELL_SDMMC_OFFSET_CLKENA       :
        printf("[QEMU][%s] NX_SDXC_CLKENA ==> \n",type);
        if (s->CLKENA & NX_SDXC_CLKENA_LOWPWR)       printf("       | NX_SDXC_CLKENA_LOWPWR\n");
        if (s->CLKENA & NX_SDXC_CLKENA_CLKENB)       printf("       | NX_SDXC_CLKENA_CLKENB\n");
        break;
    case NEXELL_SDMMC_OFFSET_CTRL         :
        printf("[QEMU][%s] NX_SDXC_CTRL ==> \n",type);
        if (s->CTRL & NX_SDXC_CTRL_USEINDMAC)        printf("       | NX_SDXC_CTRL_USEINDMAC\n");
        if (s->CTRL & NX_SDXC_CTRL_READWAIT)         printf("       | NX_SDXC_CTRL_READWAIT\n");
        if (s->CTRL & NX_SDXC_CTRL_DMAMODE_EN)       printf("       | NX_SDXC_CTRL_DMAMODE_EN\n");
        if (s->CTRL & NX_SDXC_CTRL_DMARST)           printf("       | NX_SDXC_CTRL_DMARST\n");
        if (s->CTRL & NX_SDXC_CTRL_FIFORST)          printf("       | NX_SDXC_CTRL_FIFORST\n");
        if (s->CTRL & NX_SDXC_CTRL_CTRLRST)          printf("       | NX_SDXC_CTRL_CTRLRST\n");
        break;
    case NEXELL_SDMMC_OFFSET_STATUS       :
        printf("[QEMU][%s] NX_SDXC_STATUS ==> \n",type);
        if (s->STATUS & NX_SDXC_STATUS_FIFOCOUNT)    printf("       | NX_SDXC_STATUS_FIFOCOUNT\n");
        if (s->STATUS & NX_SDXC_STATUS_FSMBUSY  )    printf("       | NX_SDXC_STATUS_FSMBUSY  \n");
        if (s->STATUS & NX_SDXC_STATUS_DATABUSY )    printf("       | NX_SDXC_STATUS_DATABUSY \n");
        if (s->STATUS & NX_SDXC_STATUS_FIFOFULL )    printf("       | NX_SDXC_STATUS_FIFOFULL \n");
        if (s->STATUS & NX_SDXC_STATUS_FIFOEMPTY)    printf("       | NX_SDXC_STATUS_FIFOEMPTY\n");
        break;
    case NEXELL_SDMMC_OFFSET_CMD          :
        printf("[QEMU][%s] NX_SDXC_CMD ==> \n",type);
        if (s->CMD & NX_SDXC_CMDFLAG_STARTCMD       )  printf("       | NX_SDXC_CMDFLAG_STARTCMD       \n");
        if (s->CMD & NX_SDXC_CMDFLAG_USE_HOLD_REG   )  printf("       | NX_SDXC_CMDFLAG_USE_HOLD_REG   \n");
        if (s->CMD & NX_SDXC_CMDFLAG_VOLT_SWITCH    )  printf("       | NX_SDXC_CMDFLAG_VOLT_SWITCH    \n");
        if (s->CMD & NX_SDXC_CMDFLAG_BOOT_MODE      )  printf("       | NX_SDXC_CMDFLAG_BOOT_MODE      \n");
        if (s->CMD & NX_SDXC_CMDFLAG_DISABLE_BOOT   )  printf("       | NX_SDXC_CMDFLAG_DISABLE_BOOT   \n");
        if (s->CMD & NX_SDXC_CMDFLAG_EXPECTBOOTACK  )  printf("       | NX_SDXC_CMDFLAG_EXPECTBOOTACK  \n");
        if (s->CMD & NX_SDXC_CMDFLAG_ENABLE_BOOT    )  printf("       | NX_SDXC_CMDFLAG_ENABLE_BOOT    \n");
        if (s->CMD & NX_SDXC_CMDFLAG_CCS_EXPECTED   )  printf("       | NX_SDXC_CMDFLAG_CCS_EXPECTED   \n");
        if (s->CMD & NX_SDXC_CMDFLAG_READCEATADEVICE)  printf("       | NX_SDXC_CMDFLAG_READCEATADEVICE\n");
        if (s->CMD & NX_SDXC_CMDFLAG_UPDATECLKONLY  )  printf("       | NX_SDXC_CMDFLAG_UPDATECLKONLY  \n");
        if (s->CMD & NX_SDXC_CMDFLAG_SENDINIT       )  printf("       | NX_SDXC_CMDFLAG_SENDINIT       \n");
        if (s->CMD & NX_SDXC_CMDFLAG_STOPABORT      )  printf("       | NX_SDXC_CMDFLAG_STOPABORT      \n");
        if (s->CMD & NX_SDXC_CMDFLAG_WAITPRVDAT     )  printf("       | NX_SDXC_CMDFLAG_WAITPRVDAT     \n");
        if (s->CMD & NX_SDXC_CMDFLAG_SENDAUTOSTOP   )  printf("       | NX_SDXC_CMDFLAG_SENDAUTOSTOP   \n");
        if (s->CMD & NX_SDXC_CMDFLAG_BLOCK          )  printf("       | NX_SDXC_CMDFLAG_BLOCK          \n");
        if (s->CMD & NX_SDXC_CMDFLAG_STREAM         )  printf("       | NX_SDXC_CMDFLAG_STREAM         \n");
        if (s->CMD & NX_SDXC_CMDFLAG_TXDATA         )  printf("       | NX_SDXC_CMDFLAG_TXDATA         \n");
        if (s->CMD & NX_SDXC_CMDFLAG_RXDATA         )  printf("       | NX_SDXC_CMDFLAG_RXDATA         \n");
        if (s->CMD & NX_SDXC_CMDFLAG_CHKRSPCRC      )  printf("       | NX_SDXC_CMDFLAG_CHKRSPCRC      \n");
        if (s->CMD & NX_SDXC_CMDFLAG_SHORTRSP       )  printf("       | NX_SDXC_CMDFLAG_SHORTRSP       \n");
        if (s->CMD & NX_SDXC_CMDFLAG_LONGRSP        )  printf("       | NX_SDXC_CMDFLAG_LONGRSP        \n");
        break;
    case NEXELL_SDMMC_OFFSET_RINTSTS          :
        printf("[QEMU][%s] NX_SDXC_RINTSTS ==> \n",type);
        if (s->CMD & NX_SDXC_RINTSTS_SDIO)  printf("       | NX_SDXC_RINTSTS_SDIO\n");
        if (s->CMD & NX_SDXC_RINTSTS_EBE )  printf("       | NX_SDXC_RINTSTS_EBE \n");
        if (s->CMD & NX_SDXC_RINTSTS_ACD )  printf("       | NX_SDXC_RINTSTS_ACD \n");
        if (s->CMD & NX_SDXC_RINTSTS_SBE )  printf("       | NX_SDXC_RINTSTS_SBE \n");
        if (s->CMD & NX_SDXC_RINTSTS_HLE )  printf("       | NX_SDXC_RINTSTS_HLE \n");
        if (s->CMD & NX_SDXC_RINTSTS_FRUN)  printf("       | NX_SDXC_RINTSTS_FRUN\n");
        if (s->CMD & NX_SDXC_RINTSTS_HTO )  printf("       | NX_SDXC_RINTSTS_HTO \n");
        if (s->CMD & NX_SDXC_RINTSTS_DRTO)  printf("       | NX_SDXC_RINTSTS_DRTO\n");
        if (s->CMD & NX_SDXC_RINTSTS_RTO )  printf("       | NX_SDXC_RINTSTS_RTO \n");
        if (s->CMD & NX_SDXC_RINTSTS_DCRC)  printf("       | NX_SDXC_RINTSTS_DCRC\n");
        if (s->CMD & NX_SDXC_RINTSTS_RCRC)  printf("       | NX_SDXC_RINTSTS_RCRC\n");
        if (s->CMD & NX_SDXC_RINTSTS_RXDR)  printf("       | NX_SDXC_RINTSTS_RXDR\n");
        if (s->CMD & NX_SDXC_RINTSTS_TXDR)  printf("       | NX_SDXC_RINTSTS_TXDR\n");
        if (s->CMD & NX_SDXC_RINTSTS_DTO )  printf("       | NX_SDXC_RINTSTS_DTO \n");
        if (s->CMD & NX_SDXC_RINTSTS_CD  )  printf("       | NX_SDXC_RINTSTS_CD  \n");
        if (s->CMD & NX_SDXC_RINTSTS_RE  )  printf("       | NX_SDXC_RINTSTS_RE  \n");
        break;        
    }    
}


static const MemoryRegionOps sdmmc_ops = {
    .read = sdmmc_read,
    .write = sdmmc_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4
    }
};


/* static int sdmmc_be_change(void *opaque) */
/* { */
/*     NexellSDMMCState *s = opaque; */

/*     qemu_chr_fe_set_handlers(&s->chr, sdmmc_can_rx, sdmmc_rx, sdmmc_event, */
/*         sdmmc_be_change, s, NULL, true); */

/*     return 0; */
/* } */

/*
 * Create SDMMC device.
 */
NexellSDMMCState *nexell_sdmmc_create(MemoryRegion *address_space, hwaddr base,
    qemu_irq irq)
{
    NexellSDMMCState *s = g_malloc0(sizeof(NexellSDMMCState));
    s->irq = irq;
    /* qemu_chr_fe_init(&s->chr, chr, &error_abort); */
    /* qemu_chr_fe_set_handlers(&s->chr, sdmmc_can_rx, sdmmc_rx, sdmmc_event, */
    /*     sdmmc_be_change, s, NULL, true); */
    memory_region_init_io(&s->mmio, NULL, &sdmmc_ops, s,
                          TYPE_NEXELL_SDMMC, sizeof(NexellSDMMCState));
    //NEXELL_SDMMC_MAX);
    memory_region_add_subregion(address_space, base, &s->mmio);

    return s;
}
