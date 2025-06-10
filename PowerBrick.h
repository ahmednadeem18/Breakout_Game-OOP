#pragma once
#include "Brick.h"
#include "PowerUp.h"

class PowerBrick : public Brick {
private:
    PowerUp* power;
public:
    PowerBrick(int x, int y, int w, int h, PowerUp* p)
        : Brick(x, y, w, h, 1), power(p) {
    }

    bool isPowerBrick() const override {
        return true;
    }

    PowerUp* releasePowerUp() {
        return power;
    }
};
