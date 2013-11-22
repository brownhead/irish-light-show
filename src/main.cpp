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

#include "graphics/primitives/RGBSurface.hpp"
#include "graphics/files/ImageFile.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>
#include <cstdlib>

typedef uint32_t color_t;

int main(int argc, char * argv[]) {
    if (argc == 1) {
        std::cout << "usage: " << argv[0] << " image0 image1 ..." << std::endl;
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL_video." << std::endl;
        return 1;
    }

    if (IMG_Init(0) != 0) {
        std::cerr << "Failed to initialize SDL_image." << std::endl;
        return 1;
    }

    SDL_Window * win = SDL_CreateWindow(
        "Irish Light Show", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        500, 500, SDL_WINDOW_SHOWN);
    if (win == nullptr){
       std::cerr << "Failed to create window. " << SDL_GetError() << std::endl;
       return 1;
    }


    // graphics::RGBSurface surface(100, 100);
    // surface.set_pixel(40, 5, graphics::ColorRGB(0, 0, 255));

    SDL_Surface * screen = SDL_GetWindowSurface(win);

    graphics::ImageFile a(argv[1]);

    SDL_BlitSurface(a.surface().sdl_surface(), NULL, screen, NULL);


    SDL_Delay(2000);

    SDL_DestroyWindow(win);


    IMG_Quit();
    SDL_Quit();

    return 0;
}
