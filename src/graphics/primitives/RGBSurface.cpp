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

#include "RGBSurface.hpp"

#include <SDL2/SDL.h>

#include "common/SDLException.hpp"

#include <iostream>

namespace graphics {

RGBSurface::RGBSurface() :
    surface_(nullptr), width_(0), height_(0)
{
    // Do nothing
}

RGBSurface::RGBSurface(unsigned width, unsigned height) :
        width_(width), height_(height) {
    surface_ = SDL_CreateRGBSurface(0, width, height, ColorRGB::BIT_WIDTH,
        ColorRGB::RED_MASK, ColorRGB::GREEN_MASK, ColorRGB::BLUE_MASK, 0);
    if (surface_ == nullptr) {
        throw common::SDLException();
    }
    if (SDL_MUSTLOCK(surface_) == SDL_TRUE) {
        // This error should never occur
        throw common::SDLException("RGBSurface is requiring a lock");
    }
}

RGBSurface::RGBSurface(SDL_Surface * surface, bool convert) :
        width_(0), height_(0) {
    if (surface == nullptr) {
        throw std::invalid_argument("surface cannot be null");
    }

    if (convert) {
        SDL_Surface * converted_surface = SDL_ConvertSurfaceFormat(surface,
            ColorRGB::PIXEL_FORMAT, 0);
        if (converted_surface == nullptr) {
            throw common::SDLException();
        }
        surface_ = converted_surface;
    } else {
        surface_ = surface;
    }

    width_ = surface_->w;
    height_ = surface_->h;
}

RGBSurface::~RGBSurface() {
    if (surface_ != nullptr) {
        SDL_FreeSurface(surface_);
        surface_ = nullptr;
    }
}

void RGBSurface::set_pixel(unsigned x, unsigned y, ColorRGB color) {
    if (surface_ == nullptr) {
        throw std::runtime_error("surface is null.");
    } else if (x >= width_ || y >= height_) {
        throw std::out_of_range("x and/or y are out of range.");
    }

    auto start_of_row = reinterpret_cast<uint8_t *>(surface_->pixels) +
        surface_->pitch * y;
    auto target = reinterpret_cast<uint32_t *>(start_of_row +
        x * ColorRGB::BIT_WIDTH);
    *target = color.value() | (*target & 0x000000FF);
}

ColorRGB RGBSurface::get_pixel(unsigned x, unsigned y) const {
    if (surface_ == nullptr) {
        throw std::runtime_error("surface is null.");
    } else if (x >= width_ || y >= height_) {
        throw std::out_of_range("x and/or y are out of range.");
    }

    auto start_of_row = reinterpret_cast<uint8_t *>(surface_->pixels) +
        surface_->pitch * y;
    auto target = reinterpret_cast<uint32_t *>(start_of_row +
        x * ColorRGB::BIT_WIDTH);
    return ColorRGB(*target & 0xFFFFFF00);
}

SDL_Surface * RGBSurface::sdl_surface() {
    return surface_;
}

unsigned RGBSurface::width() const {
    return width_;
}

unsigned RGBSurface::height() const {
    return height_;
}

} // namespace graphics
