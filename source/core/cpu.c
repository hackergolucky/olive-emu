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

#include "core/cpu.h"
#include "core/bus.h"


void mCpu_init(mCpu *cpu)
{
    // Starting value of P is 0x34
    cpu->p.i = TRUE;
    cpu->p.b = TRUE;
    // A, X, Y are all 0
    cpu->a = 0;
    cpu->x = 0;
    cpu->y = 0;
    // SP starts at $FD
    cpu->sp = 0xFD;
    // Initialize memory map to 0s
    mBus_zeroMem(&cpu->map);
}

uint8_t mCpu_fetch(mCpu *cpu)
{
    uint8_t byte = mBus_read8(&cpu->map, cpu->pc);
    ++cpu->pc;
    return byte;
}

int mCpu_runforCycles(mCpu *cpu, int cycles)
{
    while(cycles > 0)
    {
        uint8_t opcode = mCpu_fetch(cpu);
    }
    
    // return overspent cycles
    return cycles;
}
