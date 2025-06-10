#pragma once
#include "Brick.h"

class UnbreakableBrick : public Brick {
public:
    UnbreakableBrick(int x, int y, int w, int h)
        : Brick(x, y, w, h, -1) {
    }

    void hit() override {}

    bool isDestroyed() const override {
        return false;
    }
};
