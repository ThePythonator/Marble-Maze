#include "game.hpp"
#include "assets.hpp"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define SPRITE_SIZE 8

#define SPEED 4
#define ACCELERATION 4

using namespace blit;

struct Ball {
    float xPosition, yPosition;
    float xVelocity, yVelocity;
};

int state = 0;
float dt;
uint32_t lastTime = 0;

Ball marble;

float min(float a, float b) {
    return a < b ? a : b;
}

float max(float a, float b) {
    return a > b ? a : b;
}

float clamp(float x, float mi, float ma) {
    return min(max(x, mi), ma);
}

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init() {
    set_screen_mode(ScreenMode::hires);

    marble.xPosition = marble.yPosition = 60; //remove later
}

///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the 
// amount if milliseconds elapsed since the start of your game
//
void render(uint32_t time) {

    // clear the screen -- screen is a reference to the frame buffer and can be used to draw all things with the 32blit
    screen.clear();

    // draw some text at the top of the screen
    screen.alpha = 255;
    screen.mask = nullptr;
    screen.pen = Pen(255, 255, 255);
    //screen.rectangle(Rect(0, 0, 320, 14));
    screen.text(std::to_string(tilt.x), minimal_font, Point(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2), true, TextAlign::right);
    screen.text(std::to_string(tilt.y), minimal_font, Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), true, TextAlign::left);



    screen.rectangle(Rect(marble.xPosition - SPRITE_SIZE / 2, marble.yPosition - SPRITE_SIZE / 2, SPRITE_SIZE, SPRITE_SIZE));

    screen.pen = Pen(0, 0, 0);
    screen.text("Hello 32blit!", minimal_font, Point(5, 4));

    //screen.text(std::to_string(blit::tilt.x) + ", " + std::to_string(blit::tilt.y))
    
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the 
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
    dt = (time - lastTime) / 1000.0;
    lastTime = time;

    marble.xVelocity += tilt.x * tilt.x * ACCELERATION; //blit::tilt.x * ACCELERATION; //squared for damping
    marble.yVelocity += tilt.y * tilt.y * ACCELERATION; //blit::tilt.y * ACCELERATION;

    marble.xPosition += marble.xVelocity * dt * SPEED;
    marble.yPosition += marble.yVelocity * dt * SPEED;

    if (marble.xPosition < SPRITE_SIZE / 2) {
        marble.xPosition = SPRITE_SIZE / 2;
        marble.xVelocity = 0;
    }
    else if (marble.xPosition > SCREEN_WIDTH - SPRITE_SIZE / 2) {
        marble.xPosition = SCREEN_WIDTH - SPRITE_SIZE / 2;
        marble.xVelocity = 0;
    }

    if (marble.yPosition < SPRITE_SIZE / 2) {
        marble.yPosition = SPRITE_SIZE / 2;
        marble.yVelocity = 0;
    }
    else if (marble.yPosition > SCREEN_HEIGHT - SPRITE_SIZE / 2) {
        marble.yPosition = SCREEN_HEIGHT - SPRITE_SIZE / 2;
        marble.yVelocity = 0;
    }
}