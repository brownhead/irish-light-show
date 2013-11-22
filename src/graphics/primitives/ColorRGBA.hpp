#pragma once

#include <stdint.h>

namespace graphics {

struct ColorRGBA {
	ColorRGBA() = default;
	ColorRGBA(uint32_t value);
	ColorRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
	uint32_t value() const;

	static uint32_t const RED_MASK = 0xFF << 24;
	static uint32_t const GREEN_MASK = 0xFF << 16;
	static uint32_t const BLUE_MASK = 0xFF << 8;
	static uint32_t const ALPHA_MASK = 0xFF;

	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
};

} // namespace graphics
