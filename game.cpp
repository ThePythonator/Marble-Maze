#include "game.hpp"
#include "assets.hpp"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define SPRITE_SIZE 8

#define LEVEL_COUNT 2
// LEVEL_LENGTH is total number of possible wall blocks
#define LEVEL_LENGTH 1200

#define SPEED 100
#define ACCELERATION 8

#define MAX_VELOCITY 2

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

struct Finish {
    int xPosition, yPosition;
};

void load_level(int);

enum State {
    title,
    game
};

State state = State::title;

float dt;
uint32_t lastTime = 0;

Ball marble;
Finish finish;

std::vector<Wall> walls;

Surface* background = Surface::load(asset_background);

int currentLevel;

int levelLayouts[LEVEL_COUNT][LEVEL_LENGTH] = {
    {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4, 11,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1,  4, 11,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,  3, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1,  2,  7,  7,  7,  7,  7,  7,  7,  7, 10, 11,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    },
    {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4, 11,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  6,  6,  6,  6,  8,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  7,  7,  7,  7, 10,  5, -1, -1, -1, -1,  0,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1,  4, 11,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,  3, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  9,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6,  6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4, 11,  7,  7,  7,  7,  7,  7,  7,  7, 10, 11,  7,  7,  7,  7,  7,  7,  7,  7, 10, 11,  7,  7,  7,  7,  7,  7,  7,  7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,  3, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1,  2,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  0,  6,  6,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1,  0,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4, 12, 12,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,  3, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4, 12, 12,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  2,  7,  7,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4,  5, -1, -1, -1, -1, -1, -1, -1, -1
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

void render_finish() {
    screen.blit(screen.sprites, Rect(0, 32, 16, 16), Point(finish.xPosition - SPRITE_SIZE, finish.yPosition - SPRITE_SIZE));
}

bool colliding(Wall wall) {
    return (marble.xPosition > wall.xPosition - SPRITE_SIZE && marble.xPosition < wall.xPosition + SPRITE_SIZE) && (marble.yPosition > wall.yPosition - SPRITE_SIZE && marble.yPosition < wall.yPosition + SPRITE_SIZE);
}

bool hit_finish(Finish finish) {
    return (marble.xPosition - SPRITE_SIZE / 2 > finish.xPosition - SPRITE_SIZE && marble.xPosition + SPRITE_SIZE / 2 < finish.xPosition + SPRITE_SIZE) && (marble.yPosition - SPRITE_SIZE / 2 > finish.yPosition - SPRITE_SIZE && marble.yPosition + SPRITE_SIZE / 2 < finish.yPosition + SPRITE_SIZE);
}

void handle_collisions() {
    int roughX, roughY;
    roughX = (marble.xPosition - SPRITE_SIZE / 2) / SPRITE_SIZE;
    roughY = (marble.yPosition - SPRITE_SIZE / 2) / SPRITE_SIZE;

    // check blocks at roughX to roughX + 1 (Same with y)

    for (int i = 0; i < walls.size(); i++) {
        if (walls.at(i).x == roughX || walls.at(i).x == roughX + 1) {
            if (walls.at(i).y == roughY || walls.at(i).y == roughY + 1) {
                if (colliding(walls.at(i))) {
                    // collided with wall.at(i)

                    if (walls.at(i).type == 0 || walls.at(i).type == 1 || walls.at(i).type == 2 || walls.at(i).type == 3) {
                        //corner
                        while (colliding(walls.at(i))) {
                            marble.xPosition -= tilt.x * std::abs(tilt.x) * (marble.xVelocity > 0 ? 1 : -1);
                            marble.yPosition -= tilt.x * std::abs(tilt.x) * (marble.yVelocity > 0 ? 1 : -1);
                        }
                        if (marble.xPosition + SPRITE_SIZE / 2 >= walls.at(i).xPosition && marble.xPosition - SPRITE_SIZE / 2 <= walls.at(i).xPosition + SPRITE_SIZE * 2) {
                            marble.yVelocity = -0.1 * marble.yVelocity;
                        }
                        else {
                            marble.xVelocity = -0.1 * marble.xVelocity;
                        }
                    }/*
                    else if (walls.at(i).type == 1) {
                        //corner
                    }
                    else if (walls.at(i).type == 2) {
                        //corner
                    }
                    else if (walls.at(i).type == 3) {
                        //corner
                    }*/
                    else if (walls.at(i).type == 4) {
                        marble.xVelocity = -0.1 * marble.xVelocity;
                        marble.xPosition = walls.at(i).xPosition - SPRITE_SIZE;
                    }
                    else if (walls.at(i).type == 5) {
                        marble.xVelocity = -0.1 * marble.xVelocity;
                        marble.xPosition = walls.at(i).xPosition + SPRITE_SIZE;
                    }
                    else if (walls.at(i).type == 6) {
                        marble.yVelocity = -0.1 * marble.yVelocity;
                        marble.yPosition = walls.at(i).yPosition - SPRITE_SIZE;
                    }
                    else if (walls.at(i).type == 7) {
                        marble.yVelocity = -0.1 * marble.yVelocity;
                        marble.yPosition = walls.at(i).yPosition + SPRITE_SIZE;
                    }
                    // ignore 8...12 because they are always surrounded by other blocks
                }
            }
        }
    }
}

void start_game() {
    // position defaults
    marble.xPosition = SCREEN_WIDTH / 2;
    marble.yPosition = SCREEN_HEIGHT / 2;

    marble.xPosition = SCREEN_WIDTH - SPRITE_SIZE;
    marble.yPosition = SCREEN_HEIGHT - SPRITE_SIZE;

    load_level(0);
}

void load_level(int levelNumber) {
    walls.clear();

    if (levelNumber < LEVEL_COUNT) {
        currentLevel = levelNumber;

        for (int i = 0; i < LEVEL_LENGTH; i++) {
            Wall wall;
            wall.type = levelLayouts[levelNumber][i];
            if (wall.type == -1) {
                // is nothing
            }
            else if (wall.type == -2) {
                // is the start
                marble.xPosition = (i % (SCREEN_WIDTH / SPRITE_SIZE) + 0.5) * SPRITE_SIZE;
                marble.yPosition = (i / (SCREEN_WIDTH / SPRITE_SIZE) + 0.5) * SPRITE_SIZE;
            }
            else if (wall.type == -3) {
                // is the finish
                finish.xPosition = (i % (SCREEN_WIDTH / SPRITE_SIZE) + 1) * SPRITE_SIZE;
                finish.yPosition = (i / (SCREEN_WIDTH / SPRITE_SIZE) + 1) * SPRITE_SIZE;
            }
            else {
                // is a wall block
                wall.x = i % (SCREEN_WIDTH / SPRITE_SIZE);
                wall.y = i / (SCREEN_WIDTH / SPRITE_SIZE);

                wall.xPosition = (wall.x + 0.5) * SPRITE_SIZE;
                wall.yPosition = (wall.y + 0.5) * SPRITE_SIZE;

                walls.push_back(wall);
            }
        }
    }
    else {
        load_level(0); // need to have at least one level otherwise bad things might happen
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
    screen.sprites = Surface::load(asset_sprites);
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

    screen.blit(background, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), Point(0, 0), false);
    
    if (state == State::title) {
        screen.text("Marble Maze", minimal_font, Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3), true, TextAlign::center_center);
        screen.text("Press A to start", minimal_font, Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 3), true, TextAlign::center_center);
    }
    else if (state == State::game) {
        //screen.text(std::to_string(tilt.x), minimal_font, Point(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2), true, TextAlign::right);
        //screen.text(std::to_string(tilt.y), minimal_font, Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), true, TextAlign::left);

        for (int i = 0; i < walls.size(); i++) {
            render_wall(walls.at(i));
        }

        render_finish();

        render_ball();

        //screen.rectangle(Rect(marble.xPosition - SPRITE_SIZE / 2, marble.yPosition - SPRITE_SIZE / 2, SPRITE_SIZE, SPRITE_SIZE));
    }

    //screen.text(std::to_string(state), minimal_font, Point(20, 20));

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
    
    if (state == State::title) {
        if (buttons.pressed & Button::A) {
            state = State::game;
            start_game();
        }
    }
    else if (state == State::game) {
        marble.xVelocity += tilt.x * std::abs(tilt.x) * ACCELERATION * dt; //blit::tilt.x * ACCELERATION; //squared for damping
        marble.yVelocity += tilt.y * std::abs(tilt.y) * ACCELERATION * dt; //blit::tilt.y * ACCELERATION;

        marble.xVelocity = clamp(marble.xVelocity, -MAX_VELOCITY, MAX_VELOCITY);
        marble.yVelocity = clamp(marble.yVelocity, -MAX_VELOCITY, MAX_VELOCITY);


        marble.xPosition += marble.xVelocity * dt * SPEED;
        marble.yPosition += marble.yVelocity * dt * SPEED;

        if (marble.xPosition < SPRITE_SIZE / 2) {
            marble.xPosition = SPRITE_SIZE / 2;
            marble.xVelocity = -0.1 * marble.xVelocity;
        }
        else if (marble.xPosition > SCREEN_WIDTH - SPRITE_SIZE / 2) {
            marble.xPosition = SCREEN_WIDTH - SPRITE_SIZE / 2;
            marble.xVelocity = -0.1 * marble.xVelocity;
        }

        if (marble.yPosition < SPRITE_SIZE / 2) {
            marble.yPosition = SPRITE_SIZE / 2;
            marble.yVelocity = -0.1 * marble.yVelocity;
        }
        else if (marble.yPosition > SCREEN_HEIGHT - SPRITE_SIZE / 2) {
            marble.yPosition = SCREEN_HEIGHT - SPRITE_SIZE / 2;
            marble.yVelocity = -0.1 * marble.yVelocity;
        }
        
        // check collisions
        handle_collisions();

        if (hit_finish(finish)) {
            // in finish area
            // <display level complete>?

            // next level
            load_level(currentLevel + 1);
        }
    }
}