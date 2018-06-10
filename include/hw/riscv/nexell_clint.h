/*
 * SiFive CLINT (Core Local Interruptor) interface
 *
 * Copyright (c) 2016-2017 Sagar Karandikar, sagark@eecs.berkeley.edu
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

#ifndef HW_NEXELL_CLINT_H
#define HW_NEXELL_CLINT_H

#define TYPE_NEXELL_CLINT "riscv.nexell.clint"

#define NEXELL_CLINT(obj) \
    OBJECT_CHECK(NexellCLINTState, (obj), TYPE_NEXELL_CLINT)

typedef struct NexellCLINTState {
    /*< private >*/
    SysBusDevice parent_obj;

    /*< public >*/
    MemoryRegion mmio;
    uint32_t num_harts;
    uint32_t sip_base;
    uint32_t timecmp_base;
    uint32_t time_base;
    uint32_t aperture_size;
} NexellCLINTState;

DeviceState *nexell_clint_create(hwaddr addr, hwaddr size, uint32_t num_harts,
    uint32_t sip_base, uint32_t timecmp_base, uint32_t time_base);

enum {
    NEXELL_SIP_BASE     = 0x0,
    NEXELL_TIMECMP_BASE = 0x4000,
    NEXELL_TIME_BASE    = 0xBFF8
};

#endif
