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

#include "ColorRGB.hpp"

namespace graphics {

ColorRGB::ColorRGB(uint32_t value) : red(value >> 24),
        green(value >> 16 & 0xFF), blue(value >> 8 & 0xFF) {
    // Do nothing
}

ColorRGB::ColorRGB(uint8_t red, uint8_t green, uint8_t blue) :
        red(red), green(green), blue(blue) {
    // Do nothing
}

uint32_t ColorRGB::value() const {
    return red << 24 | green << 16 | blue << 8;
}

} // namespace graphics
