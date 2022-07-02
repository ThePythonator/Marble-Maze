#include "Constants.hpp"

namespace MarbleMaze {
	namespace Constants {
		const uint16_t SCREEN_WIDTH = 320;
		const uint16_t SCREEN_HEIGHT = 240;
		
		const uint8_t SPRITE_SIZE = 8;

		const float TILT_FORCE = 10000.0f;
		const float DRAG_SCALE = 40.0f;

		const uint8_t LEVEL_COUNT = 1;

		namespace Strings {
			const std::string TITLE_TEXT = "Marble Maze";

#ifdef TARGET_32BLIT_HW
			const std::string PLAY_TEXT = "Press A to start";
#else
			const std::string PLAY_TEXT = "Press U to start";
#endif
		}

		namespace Timings {
			const float FLASHY_TEXT_ON = 0.7f;
			const float FLASHY_TEXT_OFF = 0.5f;

			const float CROSSFADE_DURATION = 2.5f;
		}

		namespace Tiles {
			namespace Walls {
				const uint8_t STRAIGHT_LEFT = 4;
				const uint8_t STRAIGHT_RIGHT = 5;
				const uint8_t STRAIGHT_TOP = 6;
				const uint8_t STRAIGHT_BOTTOM = 7;

				const uint8_t INSIDE_CORNER_TOP_LEFT = 8;
				const uint8_t INSIDE_CORNER_TOP_RIGHT = 9;
				const uint8_t INSIDE_CORNER_BOTTOM_LEFT = 10;
				const uint8_t INSIDE_CORNER_BOTTOM_RIGHT = 11;

				const uint8_t OUTSIDE_CORNER_TOP_LEFT = 0;
				const uint8_t OUTSIDE_CORNER_TOP_RIGHT = 1;
				const uint8_t OUTSIDE_CORNER_BOTTOM_LEFT = 2;
				const uint8_t OUTSIDE_CORNER_BOTTOM_RIGHT = 3;

				const std::vector<uint8_t> ALL = {
					STRAIGHT_LEFT, STRAIGHT_RIGHT, STRAIGHT_TOP, STRAIGHT_BOTTOM,
					INSIDE_CORNER_TOP_LEFT, INSIDE_CORNER_TOP_RIGHT, INSIDE_CORNER_BOTTOM_LEFT, INSIDE_CORNER_BOTTOM_RIGHT,
					OUTSIDE_CORNER_TOP_LEFT, OUTSIDE_CORNER_TOP_RIGHT, OUTSIDE_CORNER_BOTTOM_LEFT, OUTSIDE_CORNER_BOTTOM_RIGHT
				};
			}

			namespace Start {
				const uint8_t TOP_LEFT = 66;
				const uint8_t TOP_RIGHT = 67;
				const uint8_t BOTTOM_LEFT = 82;
				const uint8_t BOTTOM_RIGHT = 83;

				const std::vector<uint8_t> ALL = {
					TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
				};
			}

			namespace Finish {
				const uint8_t TOP_LEFT = 64;
				const uint8_t TOP_RIGHT = 65;
				const uint8_t BOTTOM_LEFT = 80;
				const uint8_t BOTTOM_RIGHT = 81;

				const std::vector<uint8_t> ALL = {
					TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
				};
			}

			const uint8_t BALL = 17;
		}
	}
}