#include "MarbleMaze.hpp"
#include "Assets.hpp"

using namespace blit;
using namespace MarbleMaze;


float last_time = 0.0f;

Surface* background = Surface::load(asset_background);

Utilities::Timer flashy_text_timer = Utilities::Timer(Constants::Timings::FLASHY_TEXT_OFF + Constants::Timings::FLASHY_TEXT_ON);

Level current_level;

const uint8_t* level_data[] = {
    asset_level_0
};

enum class GameState {
    Menu,
    Game
} current_state;


void init() {
    set_screen_mode(ScreenMode::hires);
    screen.sprites = Surface::load(asset_sprites);

    flashy_text_timer.start();
}

void render(uint32_t time) {
    screen.clear();

    screen.alpha = 255;
    screen.mask = nullptr;
    screen.pen = Pen(255, 255, 255);

    screen.blit(background, Rect(0, 0, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT), Point(0, 0));

    switch (current_state) {
    case GameState::Menu:
        screen.text(Constants::Strings::TITLE_TEXT, minimal_font, Point(Constants::SCREEN_WIDTH / 2, 10), true, top_center);

        if (flashy_text_timer.time() < Constants::Timings::FLASHY_TEXT_ON) screen.text(Constants::Strings::PLAY_TEXT, minimal_font, Point(Constants::SCREEN_WIDTH / 2, Constants::SCREEN_HEIGHT - 10), true, bottom_center);
        
        break;

    case GameState::Game:
        current_level.render(&screen);

        if (current_level.complete()) {
            screen.pen = Pen(rand() % 256, rand() % 256, rand() % 256);
            screen.text("Well done", minimal_font, Point(Constants::SCREEN_WIDTH / 2, 10), true, top_center);
            screen.pen = Pen(255, 255, 255);
        }

        break;

    default:
        break;
    }
}

void update(uint32_t time) {
    // Get dt
    float dt = (time - last_time) / 1000.0;
    last_time = time;

    // Cap dt
    if (dt > 0.05f) dt = 0.05f;

    // Handle buttons etc
    switch (current_state) {
    case GameState::Menu:
        flashy_text_timer.update(dt);

        if (buttons & Button::A) {
            // Create level
            current_level = Level(level_data[0]); // TODO: change to select level number?

            current_state = GameState::Game;
        }
        break;

    case GameState::Game:
        current_level.update(dt);
        break;

    default:
        break;
    }
}