#pragma once

#include <stdexcept>
#include <string>

namespace common {

class SDLException : public virtual std::runtime_error {
public:
	SDLException();
	SDLException(std::string const what);
};

} // namespace common
