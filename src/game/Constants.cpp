#include "Constants.hpp"

namespace MarbleMaze {
	namespace Constants {
		const uint16_t SCREEN_WIDTH = 320;
		const uint16_t SCREEN_HEIGHT = 240;
		
		const uint8_t SPRITE_SIZE = 8;

		const float TILT_FORCE = 10.0f;

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
	}
}