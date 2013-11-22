// Copyright (c) 2013 John Sullivan
// Copyright (c) 2013 Other contributers as noted in the CONTRIBUTERS file
//
// This file is part of Irish Light Show
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "graphics/primitives/RGBASurface.hpp"

#include <SDL2/SDL.h>

#include <iostream>

typedef uint32_t color_t;

int main() {
    SDL_Window * win = SDL_CreateWindow(
        "Irish Light Show", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        100, 100, SDL_WINDOW_SHOWN);
    if (win == nullptr){
       std::cerr << "Failed to create window. " << SDL_GetError() << std::endl;
       return 1;
    }

    graphics::RGBASurface surface(100, 100);
    surface.set_pixel(40, 5, graphics::ColorRGBA(0, 0, 255, 255));

    SDL_Surface * screen = SDL_GetWindowSurface(win);

    // SDL_Rect r = {0, 0, 20, 20};
    SDL_BlitSurface(surface.surface(), NULL, screen, NULL);

    SDL_UpdateWindowSurface(win);

    SDL_Delay(2000);

    // SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}
