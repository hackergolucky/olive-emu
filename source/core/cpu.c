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

#include <stdio.h>
#include "core/cpu.h"
#include "core/cart.h"
#include "nes.h"


void mCpu_init(struct mCpu *cpu)
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
    for(int i = 0; i < 0x800; i++)
        cpu->ram[i] = 0x00;
}

uint8_t mCpu_fetch(struct mCpu *cpu)
{
    uint8_t byte = mCpu_read8(cpu, cpu->pc);
    ++cpu->pc;
    return byte;
}

int mCpu_runforCycles(struct mCpu *cpu, int cycles)
{
    while(cycles > 0)
    {
        uint8_t opcode = mCpu_fetch(cpu);
    }
    
    // return overspent cycles
    return cycles;
}

uint8_t mCpu_read8(struct mCpu *cpu, uint16_t addr)
{
    if(addr < 0x2000) {
        addr &= 0x7FF;
        return cpu->ram[addr];
    }
    else if(addr >= 0x2000 && addr < 0x4000) {
        addr &= 0x2007;
        printf("PPU register read: $%X\n", addr);
    }
    else if(addr >= 0x4000 && addr < 0x4020) {
        printf("APU/IO register read: $%X\n", addr);
    }
    else if(addr >= 0x4020) {
        printf("Cart read: $%X\n", addr);
        return mCart_read8(gNES->cart, addr);
    }

    return 0xFF;
}

void mCpu_write8(struct mCpu *cpu, uint16_t addr, uint8_t byte)
{

}
