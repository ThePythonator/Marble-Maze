#pragma once

#include <cstdint>
#include <string>

namespace MarbleMaze {
	namespace Constants {
		extern const uint16_t SCREEN_WIDTH;
		extern const uint16_t SCREEN_HEIGHT;

		extern const uint8_t SPRITE_SIZE;

		extern const float TILT_FORCE;

		namespace Strings {
			extern const std::string TITLE_TEXT;
			extern const std::string PLAY_TEXT;
		}

		namespace Timings {
			extern const float FLASHY_TEXT_ON;
			extern const float FLASHY_TEXT_OFF;

			extern const float CROSSFADE_DURATION;
		}
	}
}