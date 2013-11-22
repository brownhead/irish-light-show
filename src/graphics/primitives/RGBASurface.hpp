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

#include "graphics/primitives/ColorRGBA.hpp"

class SDL_Surface;

namespace graphics {

class RGBASurface {
	SDL_Surface * surface_;
	unsigned width_;
	unsigned height_;
public:
	RGBASurface(unsigned width, unsigned height);
    ~RGBASurface();
	void set_pixel(unsigned x, unsigned y, ColorRGBA color);
    ColorRGBA get_pixel(unsigned x, unsigned y) const;
    SDL_Surface * surface();
    unsigned width() const;
    unsigned height() const;
};

} // namespace graphics
