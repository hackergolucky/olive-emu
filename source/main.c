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
#include "window.h"
#include "nes.h"


int main(int argc, char **argv)
{
    printf("Welcome to Olive!\n");

    gNES = (mNES *) malloc(sizeof(mNES));
    mNES_init(gNES);

    mWindow *window = (mWindow *) malloc(sizeof(mWindow));
    if(mWindow_init(window) != 0)
        goto end;

    while(window->running == TRUE)
    {
        mWindow_update(window);
    }

end:
    mWindow_destroy(window);
    mNES_destroy(gNES);
    free(window);
    free(gNES);

    return 0;
}
