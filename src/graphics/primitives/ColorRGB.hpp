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

#pragma once

#include <SDL2/SDL.h>

#include <stdint.h>

namespace graphics {

struct ColorRGB {
    ColorRGB() = default;
    ColorRGB(uint32_t value);
    ColorRGB(uint8_t red, uint8_t green, uint8_t blue);
    uint32_t value() const;

    static unsigned const BIT_WIDTH = 24;
    static uint32_t const PIXEL_FORMAT = SDL_PIXELFORMAT_RGB888;
    static uint32_t const RED_MASK = 0xFF << 16;
    static uint32_t const GREEN_MASK = 0xFF << 8;
    static uint32_t const BLUE_MASK = 0xFF;

    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

} // namespace graphics
