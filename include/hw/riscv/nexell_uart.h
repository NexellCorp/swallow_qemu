/*
 * SiFive UART interface
 *
 * Copyright (c) 2016 Stefan O'Rear
 * Copyright (c) 2017 SiFive, Inc.
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

#ifndef HW_NEXELL_UART_H
#define HW_NEXELL_UART_H

enum {
	NEXELL_UART_RBR		= 0,
	NEXELL_UART_THR		= 0,
	NEXELL_UART_DLL		= 0,
	NEXELL_UART_IER		= 4,
	NEXELL_UART_DLH		= 4,
	NEXELL_UART_IIR		= 8,
	NEXELL_UART_FCR		= 8,
	NEXELL_UART_LCR		= 12,
	NEXELL_UART_MCR		= 16,
	NEXELL_UART_LSR		= 20,
	NEXELL_UART_MSR		= 24,
	NEXELL_UART_SCR		= 28,
	NEXELL_UART_LPDLL	= 32,
	NEXELL_UART_LPDLH	= 36,
	NEXELL_UART_SRBR0	= 48,
	NEXELL_UART_STHR0	= 48,
	NEXELL_UART_SRBR1	= 52,
	NEXELL_UART_STHR1	= 52,
	NEXELL_UART_SRBR2	= 56,
	NEXELL_UART_STHR2	= 56,
	NEXELL_UART_SRBR3	= 60,
	NEXELL_UART_STHR3	= 60,
	NEXELL_UART_SRBR4	= 64,
	NEXELL_UART_STHR4	= 64,
	NEXELL_UART_SRBR5	= 68,
	NEXELL_UART_STHR5	= 68,
	NEXELL_UART_SRBR6	= 72,
	NEXELL_UART_STHR6	= 72,
	NEXELL_UART_SRBR7	= 76,
	NEXELL_UART_STHR7	= 76,
	NEXELL_UART_SRBR8	= 80,
	NEXELL_UART_STHR8	= 80,
	NEXELL_UART_SRBR9	= 84,
	NEXELL_UART_STHR9	= 84,
	NEXELL_UART_SRBR10	= 88,
	NEXELL_UART_STHR10	= 88,
	NEXELL_UART_SRBR11	= 92,
	NEXELL_UART_STHR11	= 92,
	NEXELL_UART_SRBR12	= 96,
	NEXELL_UART_STHR12	= 96,
	NEXELL_UART_SRBR13	= 100,
	NEXELL_UART_STHR13	= 100,
	NEXELL_UART_SRBR14	= 104,
	NEXELL_UART_STHR14	= 104,
	NEXELL_UART_SRBR15	= 108,
	NEXELL_UART_STHR15	= 108,
	NEXELL_UART_FAR		= 112,
	NEXELL_UART_TFR		= 116,
	NEXELL_UART_RFW		= 120,
	NEXELL_UART_USR		= 124,
	NEXELL_UART_TFL		= 128,
	NEXELL_UART_RFL		= 132,
	NEXELL_UART_SRR		= 136,
	NEXELL_UART_SRTS	= 140,
	NEXELL_UART_SBCB	= 144,
	NEXELL_UART_SDMAM	= 148,
	NEXELL_UART_SFE		= 152,
	NEXELL_UART_SRT		= 156,
	NEXELL_UART_STET	= 160,
	NEXELL_UART_HTX		= 164,
	NEXELL_UART_DMASA	= 168,
	NEXELL_UART_TCR		= 172,
	NEXELL_UART_DOER	= 176,
	NEXELL_UART_ROER	= 180,
	NEXELL_UART_DOETR	= 184,
	NEXELL_UART_TATR	= 188,
	NEXELL_UART_DLF		= 192,
	NEXELL_UART_RAR		= 196,
	NEXELL_UART_TAR		= 200,
	NEXELL_UART_LECR	= 204,
	NEXELL_UART_CPR		= 244,
	NEXELL_UART_UCV		= 248,
	NEXELL_UART_CTR		= 252,
	NEXELL_UART_MAX		= 252
};

enum {
	NEXELL_UART_IE_ERBFI	= 1,  /* Receive watermark interrupt enable */
	NEXELL_UART_IE_ETBEI	= 2 /* Transmit watermark interrupt enable */
};

enum {
	NEXELL_UART_IP_TXWM       = 1, /* Transmit watermark interrupt pending */
	NEXELL_UART_IP_RXWM       = 2  /* Receive watermark interrupt pending */
};

#define TYPE_NEXELL_UART "riscv.nexell.uart"

#define NEXELL_UART(obj) \
	OBJECT_CHECK(NexellUARTState, (obj), TYPE_NEXELL_UART)

typedef struct NexellUARTState {
	/*< private >*/
	SysBusDevice parent_obj;

    /*< public >*/
	qemu_irq irq;
	MemoryRegion mmio;
	CharBackend chr;
	uint8_t rx_fifo[16];
	unsigned int rx_fifo_len;
	uint32_t rbr;
	uint32_t thr;
	uint32_t dll;
	uint32_t ier;
	uint32_t dlh;
	uint32_t iir;
	uint32_t fcr;
	uint32_t lcr;
	uint32_t mcr;
	uint32_t lsr;
	uint32_t msr;
	uint32_t scr;
	uint32_t lpdll;
	uint32_t lpdlh;
	uint32_t srbr[16];
	uint32_t sthr[16];
	uint32_t far;
	uint32_t tfr;
	uint32_t rfw;
	uint32_t usr;
	uint32_t tfl;
	uint32_t rfl;
	uint32_t srr;
	uint32_t srts;
	uint32_t sbcb;
	uint32_t sdmam;
	uint32_t sfe;
	uint32_t srt;
	uint32_t stet;
	uint32_t htx;
	uint32_t dmasa;
	uint32_t tcr;
	uint32_t doer;
	uint32_t roer;
	uint32_t doetr;
	uint32_t tatr;
	uint32_t dlf;
	uint32_t rar;
	uint32_t tar;
	uint32_t lecr;
	uint32_t cpr;
	uint32_t ucv;
	uint32_t ctr;
} NexellUARTState;

NexellUARTState *nexell_uart_create(MemoryRegion *address_space, hwaddr base,
									Chardev *chr, qemu_irq irq);

#endif
