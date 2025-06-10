#pragma once
#include "Brick.h"

class HardBrick : public Brick {
public:
    HardBrick(int x, int y, int w, int h)
        : Brick(x, y, w, h, 2) {
    }
};
