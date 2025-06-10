#pragma once
#include "Brick.h"

class NormalBrick : public Brick {
public:
    NormalBrick(int x, int y, int w, int h)
        : Brick(x, y, w, h, 1) {
    }
};
