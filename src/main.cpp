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

#include "graphics/primitives/ColorRGB.hpp"
#include "graphics/primitives/RGBSurface.hpp"
#include "graphics/files/ImageFile.hpp"
#include "common/SDLException.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>
#include <cstdlib>

typedef uint32_t color_t;

// Other options at http://stackoverflow.com/a/596243/1989056
unsigned get_luminence(graphics::ColorRGB const & color) {
    return static_cast<unsigned>(
        0.299 * color.red +
        0.587 * color.green +
        0.114 * color.blue);
}

// Blends b atop a. Returns b if lumincence of b is greater than a, unless b's
// luminence is greater than cap, in which case a is returned.
void light_blend_surfaces(graphics::RGBSurface const & a,
        graphics::RGBSurface const & b, graphics::RGBSurface & out,
        unsigned cap) {
    unsigned width = std::min(a.width(), b.width());
    unsigned height = std::min(a.height(), b.height());

    if (width > out.width() || height > out.height()) {
        throw std::invalid_argument("out must not be smaller than a or b");
    }

    for (unsigned x = 0; x < width; ++x) {
        for (unsigned y = 0; y < height; ++y) {
            graphics::ColorRGB * chosen_color;

            graphics::ColorRGB a_color = a.get_pixel(x, y);
            graphics::ColorRGB b_color = b.get_pixel(x, y);
            unsigned b_lumincence = get_luminence(b_color);
            if (b_lumincence > cap) {
                chosen_color = &a_color;
            } else {
                unsigned a_lumincence = get_luminence(a_color);

                chosen_color =
                    b_lumincence > a_lumincence ? &b_color : &a_color;
            }

            out.set_pixel(x, y, *chosen_color);
        }
    }
}

int main(int argc, char * argv[]) {
    if (argc < 3) {
        std::cout << "usage: " << argv[0] << " image0 image1 ..." << std::endl;
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL_video." << std::endl;
        return 1;
    }

    // Open all the image files and load them into memory
    std::vector<graphics::ImageFile> files;
    unsigned max_width = 0, max_height = 0;
    for (int i = 1; i < argc; ++i) {
        files.emplace_back(argv[i]);

        max_width = std::max(max_width,
            files[files.size() - 1].surface().width());
        max_height = std::max(max_height,
            files[files.size() - 1].surface().height());
    }

    // Create an off-screen buffer we'll draw to
    graphics::RGBSurface buffer(max_width, max_height);

    // Get a window up
    SDL_Window * win = SDL_CreateWindow(
        "Irish Light Show", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        max_width, max_height, SDL_WINDOW_SHOWN);
    if (win == nullptr){
       std::cerr << "Failed to create window. " << SDL_GetError() << std::endl;
       return 1;
    }
    SDL_Surface * screen = SDL_GetWindowSurface(win);

    unsigned const LIGHTNESS_CAP_MAX = 255;
    unsigned const LIGHTNESS_CAP_MIN = 0;
    unsigned const LIGHTNESS_CAP_BIG_STEP = 30;
    unsigned lightness_cap = LIGHTNESS_CAP_MAX;

    bool refresh_screen = false;
    SDL_Event event;
    while (SDL_WaitEvent(&event) == 1)
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
                refresh_screen = true;
                if (event.key.keysym.sym == SDLK_UP &&
                        lightness_cap < LIGHTNESS_CAP_MAX) {
                    ++lightness_cap;
                } else if (event.key.keysym.sym == SDLK_DOWN &&
                        lightness_cap > LIGHTNESS_CAP_MIN) {
                    --lightness_cap;
                } else if (event.key.keysym.sym == SDLK_PAGEUP) {
                    lightness_cap = std::min(
                        lightness_cap + LIGHTNESS_CAP_BIG_STEP,
                        LIGHTNESS_CAP_MAX);
                } else if (event.key.keysym.sym == SDLK_PAGEDOWN) {
                    if (LIGHTNESS_CAP_MIN + LIGHTNESS_CAP_BIG_STEP >
                            lightness_cap) {
                        lightness_cap = 0;
                    } else {
                        lightness_cap -= LIGHTNESS_CAP_BIG_STEP;
                    }
                } else {
                    refresh_screen = false;
                }
                break;

            case SDL_QUIT:
                goto cleanup;
                break;
        }

        if (refresh_screen) {
            std::cout << "cap: " << lightness_cap << std::endl;
            // Blend the images from left to right
            light_blend_surfaces(files.at(0).surface(), files.at(1).surface(),
                buffer, lightness_cap);
            for (size_t i = 2; i < files.size(); ++i) {
                light_blend_surfaces(buffer, files.at(i).surface(), buffer,
                    lightness_cap);
            }

            SDL_BlitSurface(buffer.sdl_surface(), nullptr, screen, nullptr);
            SDL_UpdateWindowSurface(win);

            refresh_screen = false;
        }
    }
cleanup:

    IMG_Quit();
    SDL_Quit();

    return 0;
}
