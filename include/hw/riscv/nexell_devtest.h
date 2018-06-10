/*
 * QEMU Test Finisher interface
 *
 * Copyright (c) 2018 Nexell_Swallow, Inc.
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

#ifndef HW_NEXELL_SWALLOW_TEST_H
#define HW_NEXELL_SWALLOW_TEST_H

#define TYPE_NEXELL_SWALLOW_TEST "riscv.nexell_swallow.test"

#define NEXELL_SWALLOW_TEST(obj) \
    OBJECT_CHECK(NexellSwallowTestState, (obj), TYPE_NEXELL_SWALLOW_TEST)

typedef struct NexellSwallowTestState {
    /*< private >*/
    SysBusDevice parent_obj;

    /*< public >*/
    MemoryRegion mmio;
} NexellSwallowTestState;

enum {
    FINISHER_FAIL = 0x3333,
    FINISHER_PASS = 0x5555
};

DeviceState *nexell_swallow_test_create(hwaddr addr);

#endif
