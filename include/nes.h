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

#ifndef __NES_H__
#define __NES_H__

#include <stdio.h>
#include "boolean.h"
struct mCpu;
struct mCart;

typedef struct nes_t
{
    BOOL cartLoaded;

    struct mCpu *cpu;
    struct mCart *cart;
} mNES;

// Global NES instance
extern mNES *gNES;


void mNES_init(mNES *nes);
void mNES_destroy(mNES *nes);

#if __cplusplus
extern "C" {
#endif // __cplusplus

void mNES_openCart(mNES *nes, FILE *file);

#if __cplusplus
}
#endif // __cplusplus


#endif // __NES_H__