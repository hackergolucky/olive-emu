/*  Olive - An NES emulator written in C
 *  Copyright (C) 2021 hackergolucky (Avery Ramsey)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>
#include "boolean.h"

struct mCpu
{
    struct {
        BOOL n : 1;
        BOOL v : 1;
        BOOL b : 1;
        BOOL d : 1;
        BOOL i : 1;
        BOOL z : 1;
        BOOL c : 1;
    } p;

    uint8_t a;
    uint8_t x, y;
    uint8_t sp;
    uint16_t pc;

    uint8_t ram[0x800];
};

void mCpu_init(struct mCpu *cpu);

int mCpu_runForCycles(struct mCpu *cpu, int cycles);

uint8_t mCpu_read8(struct mCpu *cpu, uint16_t addr);
void mCpu_write8(struct mCpu *cpu, uint16_t addr, uint8_t byte);


#endif // __CPU_H__