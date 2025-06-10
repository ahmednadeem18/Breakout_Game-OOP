#pragma once
#include "Brick.h"

class PowerBrick : public Brick {
public:
    PowerBrick(int x, int y, int w, int h)
        : Brick(x, y, w, h, 1) {
    }

    bool isPowerBrick() const override {
        return true;
    }
};
