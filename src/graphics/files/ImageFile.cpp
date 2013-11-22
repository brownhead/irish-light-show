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

#include "ImageFile.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "common/SDLException.hpp"
#include "common/IMGException.hpp"

namespace graphics {

ImageFile::ImageFile(std::string file_path) : file_path_(file_path) {
    SDL_RWops * image_file = SDL_RWFromFile(file_path_.c_str(), "rb");
    if (image_file == nullptr) {
        throw common::SDLException("Failed to open file at " + file_path_);
    }

    auto free_surface = [](SDL_Surface * x) { SDL_FreeSurface(x); };
    std::unique_ptr<SDL_Surface, decltype(free_surface)> raw_surface(
        IMG_Load_RW(image_file, true), free_surface);
    if (raw_surface == nullptr) {
        throw common::IMGException("Failed to parse file at " + file_path_);
    }

    surface_.reset(new RGBSurface(raw_surface.get()));
}

ImageFile::~ImageFile() {
    // Do nothing
}

RGBSurface & ImageFile::surface() {
    return *surface_;
}

RGBSurface const & ImageFile::surface() const {
    return *surface_;
}

} // namespace graphics
