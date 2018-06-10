/*
 * QEMU SiFive PRCI (Power, Reset, Clock, Interrupt) interface
 *
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

#ifndef HW_NEXELL_PRCI_H
#define HW_NEXELL_PRCI_H

#define TYPE_NEXELL_PRCI "riscv.nexell.prci"

#define NEXELL_PRCI(obj) \
    OBJECT_CHECK(NexellPRCIState, (obj), TYPE_NEXELL_PRCI)

typedef struct NexellPRCIState {
    /*< private >*/
    SysBusDevice parent_obj;

    /*< public >*/
    MemoryRegion mmio;
} NexellPRCIState;

DeviceState *nexell_prci_create(hwaddr addr);

#endif
