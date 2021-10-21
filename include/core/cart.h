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

#ifndef __CART_H__
#define __CART_H__

#include <stdint.h>
#include "boolean.h"

struct mCart
{
    uint8_t *prgRom;
    uint8_t *chrRom;

    struct {
        uint8_t prgBanks; // 16KB banks
        uint8_t chrBanks; // 8KB banks
        
        struct {
            BOOL mirroring : 1;
            BOOL hasPrgRam : 1;
            BOOL hasTrainer : 1;
            BOOL ignoreMirroring : 1;
            uint8_t lowerMapper : 4;
        } f6;
        struct {
            BOOL vsUnisystem : 1;
            BOOL playChoice10 : 1;
            uint8_t nes2 : 2; // Must be = 2 for NES 2.0
            uint8_t upperMapper : 4;
        } f7;
        
        uint8_t prgRamBanks;

    } header;
};

BOOL mCart_init(struct mCart *cart, uint8_t *bytes);
void mCart_destroy(struct mCart *cart);

uint8_t mCart_read8(struct mCart *cart, uint16_t addr);


#endif // __CART_H__
