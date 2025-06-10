#pragma once
#include "raylib.h"

class Brick {
protected:
    int x;
    int y;
    int width;
    int height;
    int health;
public:
    Brick(int x, int y, int w, int h, int hp);
    virtual void hit();
    virtual bool isDestroyed() const;
    virtual void draw() const;
    virtual bool isPowerBrick() const;
    Rectangle getRect() const;
    virtual ~Brick() {}
};
