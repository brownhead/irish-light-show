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

#include "graphics/primitives/RGBSurface.hpp"

#include <string>
#include <memory>

namespace graphics {

class ImageFile {
    std::string file_path_;
    std::shared_ptr<RGBSurface> surface_;

public:
    ImageFile(std::string file_path);
    ~ImageFile();

    RGBSurface & surface();
    RGBSurface const & surface() const;
};

} // namespace graphics
