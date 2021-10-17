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

#include "window.h"
#include "nfd.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error Requires SDL 2.0.17! Aborting!
#endif


int mWindow_init(mWindow *window)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error! %s\n", SDL_GetError());
        return -1;
    }

    NFD_Init();

    SDL_WindowFlags winFlags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    window->sdlWindow = SDL_CreateWindow("Olive NES Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, winFlags);

    window->sdlRenderer = SDL_CreateRenderer(window->sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if(window->sdlRenderer == NULL)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window->sdlWindow);
    ImGui_ImplSDLRenderer_Init(window->sdlRenderer);

    window->running = TRUE;

    return 0;
}

void mWindow_update(mWindow *window)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if(event.type == SDL_QUIT ||
            (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window->sdlWindow)))
        {
            window->running = FALSE;
        }
    }

    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame(window->sdlWindow);
    ImGui::NewFrame();

    if(ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("Open ROM"))
            {
                nfdchar_t *outPath;
                nfdfilteritem_t filterItem = {"NES ROMs", "nes"};
                nfdresult_t res = NFD_OpenDialog(&outPath, &filterItem, 1, NULL);
                if(res == NFD_OKAY)
                {
                    printf("ROM file opened: %s\n", (char *)outPath);
                    NFD_FreePath(outPath);
                }
                else if(res == NFD_CANCEL)
                {
                    printf("User cancelled opening ROM!\n");
                }
                else
                {
                    printf("Error opening ROM!: %s\n", NFD_GetError());
                    window->running = FALSE;
                }
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    ImGui::Render();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    SDL_SetRenderDrawColor(window->sdlRenderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(window->sdlRenderer);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(window->sdlRenderer);
}

void mWindow_destroy(mWindow *window)
{
    NFD_Quit();

    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(window->sdlRenderer);
    SDL_DestroyWindow(window->sdlWindow);
    SDL_Quit();
}
