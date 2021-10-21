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

#include <stdlib.h>
#include "nes.h"
#include "core/cpu.h"
#include "core/cart.h"

mNES *gNES;


void mNES_init(mNES *nes)
{
    nes->cartLoaded = FALSE;

    nes->cpu = (struct mCpu *) malloc(sizeof(struct mCpu));
    mCpu_init(nes->cpu);
}

void mNES_destroy(mNES *nes)
{
    if(nes->cartLoaded) {
        mCart_destroy(nes->cart);

        free(nes->cart);
    }
    free(nes->cpu);
}

void mNES_openCart(mNES *nes, FILE *file)
{
    uint8_t *bytes;
    size_t fileSize;

    fseek(file, 0L, SEEK_END);
    fileSize = ftell(file);
    rewind(file);
    bytes = (uint8_t *) malloc(fileSize);
    fread((void *)bytes, sizeof(uint8_t), fileSize, file);

    nes->cart = (struct mCart *) malloc(sizeof(struct mCart));
    nes->cartLoaded = mCart_init(nes->cart, bytes);
    
    free(bytes);
}
