#include "Brick.h"

Brick::Brick(float x, float y, float width, float height) : isDestroyed(false) {
    rectangle = { x, y, width, height };
}

bool Brick::getIsDestroyed() const { return isDestroyed; }
Rectangle Brick::getRectangle() const { return rectangle; }

NormalBrick::NormalBrick(float x, float y) : Brick(x, y) {}
void NormalBrick::hit() { isDestroyed = true; }
void NormalBrick::draw() { DrawRectangleRec(rectangle, RED); }
MyStr NormalBrick::getType() const { return MyStr("Normal"); }

HardBrick::HardBrick(float x, float y) : Brick(x, y), hp(2) {}
void HardBrick::hit() {
    hp--;
    if (hp <= 0) {
        isDestroyed = true;
    }
}
void HardBrick::draw() { DrawRectangleRec(rectangle, ORANGE); }
MyStr HardBrick::getType() const { return MyStr("Hard"); }

UnbreakableBrick::UnbreakableBrick(float x, float y) : Brick(x, y) {}
void UnbreakableBrick::hit() {}
void UnbreakableBrick::draw() { DrawRectangleRec(rectangle, GRAY); }
MyStr UnbreakableBrick::getType() const { return MyStr("Unbreakable"); }

PowerBrick::PowerBrick(float x, float y) : Brick(x, y), powerReleased(false) {}
void PowerBrick::hit() {
    isDestroyed = true;
    powerReleased = true;
}
void PowerBrick::draw() { DrawRectangleRec(rectangle, PURPLE); }
MyStr PowerBrick::getType() const { return MyStr("Power"); }
bool PowerBrick::isPowerReleased() const { return powerReleased; }