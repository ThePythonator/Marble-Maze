#include "game.hpp"
#include "assets.hpp"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define SPRITE_SIZE 8

#define LEVEL_COUNT 1
// LEVEL_LENGTH is total number of possible wall blocks
#define LEVEL_LENGTH 1200

#define SPEED 100
#define ACCELERATION 5

#define MAX_VELOCITY 1

using namespace blit;

struct Ball {
    float xPosition, yPosition;
    float xVelocity, yVelocity;
};

struct Wall {
    int xPosition, yPosition;

    int x, y;
    int type;
};

int state = 0;
float dt;
uint32_t lastTime = 0;

Ball marble;

std::vector<Wall> walls;

//Surface* background = Surface::load(asset_background);

int levelLayouts[LEVEL_COUNT][LEVEL_LENGTH] = {
    {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4, 12,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    }
};

float min(float a, float b) {
    return a < b ? a : b;
}

float max(float a, float b) {
    return a > b ? a : b;
}

float clamp(float x, float mi, float ma) {
    return min(max(x, mi), ma);
}

void render_ball() {
    screen.sprite(16, Point(marble.xPosition - SPRITE_SIZE / 2, marble.yPosition - SPRITE_SIZE / 2));
}

void render_wall(Wall wall) {
    screen.sprite(wall.type, Point(wall.xPosition - SPRITE_SIZE / 2, wall.yPosition - SPRITE_SIZE / 2));
}

void handle_collisions() {
    int roughX, roughY;
    roughX = (marble.xPosition - SPRITE_SIZE / 2) / SPRITE_SIZE;
    roughY = (marble.yPosition - SPRITE_SIZE / 2) / SPRITE_SIZE;

    // check blocks at roughX to roughX + 1 (Same with y)

    for (int i = 0; i < walls.size(); i++) {
        if (walls.at(i).x == roughX || walls.at(i).x == roughX + 1) {
            if (walls.at(i).y == roughY || walls.at(i).y == roughY + 1) {
                // collided with Wall

                if (walls.at(i).type == 0) {
                    //corner
                }
                else if (walls.at(i).type == 1) {
                    //corner
                }
                else if (walls.at(i).type == 2) {
                    //corner
                }
                else if (walls.at(i).type == 3) {
                    //corner
                }
                else if (walls.at(i).type == 4) {
                    marble.xVelocity = -marble.xVelocity;
                }
                else if (walls.at(i).type == 5) {
                    marble.xVelocity = -marble.xVelocity;
                }
                else if (walls.at(i).type == 6) {
                    marble.yVelocity = -marble.yVelocity;
                }
                else if (walls.at(i).type == 7) {
                    marble.yVelocity = -marble.yVelocity;
                }
                // ignore 8...12 because they are always surrounded by other blocks
            }
        }
    }
}

void start_game() {
    marble.xPosition = marble.yPosition = 80; //remove later

    //load_level(0);
}

void load_level(int levelNumber) {
    for (int i = 0; i < LEVEL_LENGTH; i++) {
        Wall wall;
        wall.type = levelLayouts[levelNumber][i];

        if (wall.type != -1) {
            wall.x = i % (SCREEN_WIDTH / SPRITE_SIZE);
            wall.y = i / (SCREEN_WIDTH / SPRITE_SIZE);

            wall.xPosition = (wall.x + 0.5) * SPRITE_SIZE;
            wall.yPosition = (wall.y + 0.5) * SPRITE_SIZE;

            walls.push_back(wall);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init() {
    set_screen_mode(ScreenMode::hires);
    //screen.sprites = Surface::load(asset_sprites);
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

    screen.alpha = 255;
    screen.mask = nullptr;
    screen.pen = Pen(255, 255, 255);

    //screen.blit(background, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), Point(0, 0), false);

    if (state == 0) {
        screen.text("Marble Maze", minimal_font, Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3), true, TextAlign::center_center);
        screen.text("Press A to start", minimal_font, Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 3), true, TextAlign::center_center);
    }
    else if (state == 1) {
        screen.text(std::to_string(tilt.x), minimal_font, Point(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2), true, TextAlign::right);
        screen.text(std::to_string(tilt.y), minimal_font, Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), true, TextAlign::left);

        /*for (int i = 0; i < walls.size(); i++) {
            render_wall(walls.at(i));
        }*/

        //render_ball();

        screen.rectangle(Rect(marble.xPosition - SPRITE_SIZE / 2, marble.yPosition - SPRITE_SIZE / 2, SPRITE_SIZE, SPRITE_SIZE));
    }

    screen.pen = Pen(0, 0, 0);
    //screen.text("Hello 32blit!", minimal_font, Point(5, 4));

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

    if (state == 0) {
        if (buttons.pressed & Button::A) {
            state = 1;
            start_game();
        }
    }
    else if (state == 1) {
        marble.xVelocity += tilt.x * std::abs(tilt.x) * ACCELERATION * dt; //blit::tilt.x * ACCELERATION; //squared for damping
        marble.yVelocity += tilt.y * std::abs(tilt.y) * ACCELERATION * dt; //blit::tilt.y * ACCELERATION;

        marble.xVelocity = clamp(marble.xVelocity, -MAX_VELOCITY, MAX_VELOCITY);
        marble.yVelocity = clamp(marble.yVelocity, -MAX_VELOCITY, MAX_VELOCITY);


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
        
        // check collisions
    }
}