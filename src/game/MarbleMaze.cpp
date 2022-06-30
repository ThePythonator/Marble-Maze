#include "MarbleMaze.hpp"
#include "Assets.hpp"

using namespace blit;
using namespace MarbleMaze;

float last_time = 0.0f;

void init() {
    set_screen_mode(ScreenMode::hires);
    //screen.sprites = Surface::load(asset_sprites);
}

void render(uint32_t time) {
    screen.clear();

    screen.alpha = 255;
    screen.mask = nullptr;
    screen.pen = Pen(255, 255, 255);

    //screen.blit(background, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), Point(0, 0), false);
}

void update(uint32_t time) {
    float dt = (time - last_time) / 1000.0;
    last_time = time;
}