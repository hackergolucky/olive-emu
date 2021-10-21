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
#include <stdlib.h>
#include <memory.h>
#include "core/cart.h"


BOOL mCart_init(struct mCart *cart, uint8_t *bytes)
{
    if( bytes[0] != 0x4E ||
        bytes[1] != 0x45 ||
        bytes[2] != 0x53 ||
        bytes[3] != 0x1A)
    {
        printf("ERROR: Invalid ROM magic numbers!\n");
        return FALSE;
    }

    cart->header.prgBanks = bytes[4];
    cart->header.chrBanks = bytes[5];
    
    // TODO: Can these be set as a union?
    uint8_t f6 = bytes[6];
    cart->header.f6.mirroring = f6 & 0x1;
    cart->header.f6.hasPrgRam = (f6 & 0x2) >> 1;
    cart->header.f6.hasTrainer = (f6 & 0x4) >> 2;
    cart->header.f6.ignoreMirroring = (f6 & 0x8) >> 3;
    cart->header.f6.lowerMapper = (f6 & 0xF0) >> 4;
    uint8_t f7 = bytes[7];
    cart->header.f7.vsUnisystem = f7 & 0x1;
    cart->header.f7.playChoice10 = (f7 & 0x2) >> 1;
    cart->header.f7.nes2 = (f7 & 0xC) >> 2;
    cart->header.f7.upperMapper = (f7 & 0xF) >> 4;
    
    cart->header.prgRamBanks = bytes[8];

    bytes += 16;
    if(cart->header.f6.hasTrainer)
        bytes += 512;

    int prgRomSize = 0x4000 * cart->header.prgBanks;
    int chrRomSize = 0x2000 * cart->header.chrBanks;
    
    cart->prgRom = (uint8_t *) malloc(prgRomSize);
    cart->chrRom = (uint8_t *) malloc(chrRomSize);

    memcpy((void *)cart->prgRom, (void *)bytes, prgRomSize);
    bytes += prgRomSize;
    memcpy((void *)cart->chrRom, (void *)bytes, chrRomSize);
    bytes += chrRomSize;

    return TRUE;
}

void mCart_destroy(struct mCart *cart)
{
    free(cart->prgRom);
    free(cart->chrRom);
}

uint8_t mCart_read8(struct mCart *cart, uint16_t addr)
{
    return 0xFF;
}
