#include "Brick.h"
#include "raylib.h"

Brick::Brick(int x, int y, int w, int h, int hp)
    : x(x), y(y), width(w), height(h), health(hp) {
}

void Brick::hit() {
    if (health > 0) health--;
}

bool Brick::isDestroyed() const {
    return health <= 0;
}

void Brick::draw() const {
    DrawRectangle(x, y, width, height, RED);
}

bool Brick::isPowerBrick() const {
    return false;
}

Rectangle Brick::getRect() const {
    return { (float)x, (float)y, (float)width, (float)height };
}
