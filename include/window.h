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

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "SDL.h"
#include "boolean.h"

typedef struct window_t
{
    int gameW;
    int gameH;
    int scale;
    int gameX;
    int gameY;

    BOOL running;
    uint32_t *backBuffer;

    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
    SDL_Texture *sdlTexture;
} mWindow;

#if __cplusplus
extern "C" {
#endif // __cplusplus

int mWindow_init(mWindow *window);
void mWindow_update(mWindow *window);
void mWindow_destroy(mWindow *window);

#if __cplusplus
}
#endif // __cplusplus

#endif // __WINDOW_H__
