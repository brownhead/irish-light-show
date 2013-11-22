#include "SDLException.hpp"

#include <SDL2/SDL.h>

namespace common {

SDLException::SDLException() : std::runtime_error(SDL_GetError()) {
	// Do nothing
}

SDLException::SDLException(std::string const what) : std::runtime_error(what) {
	// Do nothing
}

} // namespace common
