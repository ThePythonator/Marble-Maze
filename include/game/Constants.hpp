#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace MarbleMaze {
	namespace Constants {
		extern const uint16_t SCREEN_WIDTH;
		extern const uint16_t SCREEN_HEIGHT;

		extern const uint8_t SPRITE_SIZE;

		extern const float TILT_FORCE;
		extern const float DRAG_SCALE;

		extern const uint8_t LEVEL_COUNT;

		namespace Strings {
			extern const std::string TITLE_TEXT;
			extern const std::string PLAY_TEXT;
		}

		namespace Timings {
			extern const float FLASHY_TEXT_ON;
			extern const float FLASHY_TEXT_OFF;

			extern const float CROSSFADE_DURATION;
		}

		namespace Tiles {
			namespace Walls {
				extern const uint8_t STRAIGHT_TOP_LEFT;
				extern const uint8_t STRAIGHT_TOP_RIGHT;
				extern const uint8_t STRAIGHT_BOTTOM_LEFT;
				extern const uint8_t STRAIGHT_BOTTOM_RIGHT;

				extern const uint8_t INSIDE_CORNER_TOP_LEFT;
				extern const uint8_t INSIDE_CORNER_TOP_RIGHT;
				extern const uint8_t INSIDE_CORNER_BOTTOM_LEFT;
				extern const uint8_t INSIDE_CORNER_BOTTOM_RIGHT;

				extern const uint8_t OUTSIDE_CORNER_TOP_LEFT;
				extern const uint8_t OUTSIDE_CORNER_TOP_RIGHT;
				extern const uint8_t OUTSIDE_CORNER_BOTTOM_LEFT;
				extern const uint8_t OUTSIDE_CORNER_BOTTOM_RIGHT;

				extern const std::vector<uint8_t> ALL;
			}

			namespace Start {
				extern const uint8_t TOP_LEFT;
				extern const uint8_t TOP_RIGHT;
				extern const uint8_t BOTTOM_LEFT;
				extern const uint8_t BOTTOM_RIGHT;

				extern const std::vector<uint8_t> ALL;
			}

			namespace Finish {
				extern const uint8_t TOP_LEFT;
				extern const uint8_t TOP_RIGHT;
				extern const uint8_t BOTTOM_LEFT;
				extern const uint8_t BOTTOM_RIGHT;

				extern const std::vector<uint8_t> ALL;
			}

			extern const uint8_t BALL;
		}
	}
}