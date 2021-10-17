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

#include "core/bus.h"
#include <memory.h>


void mBus_zeroMem(struct mMemMap *map)
{
    memset(map->mem, 0x00, 0x10000);
}

uint8_t mBus_read8(struct mMemMap *map, uint16_t addr)
{
    return map->mem[addr];
}

void mBus_write8(struct mMemMap *map, uint16_t addr, uint8_t byte)
{
    map->mem[addr] = byte;
}
