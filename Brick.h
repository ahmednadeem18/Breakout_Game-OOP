#ifndef BRICK_H
#define BRICK_H

#include "MyStr.h"
#include <raylib.h>

class Brick {
protected:
    Rectangle rectangle;
    bool isDestroyed;

public:
    Brick(float x, float y, float width = 60, float height = 20);
    virtual ~Brick() {}
    virtual void hit() = 0;
    virtual void draw() = 0;
    virtual bool getIsDestroyed() const;
    virtual MyStr getType() const = 0;
    Rectangle getRectangle() const;
};

class NormalBrick : public Brick {
public:
    NormalBrick(float x, float y);
    void hit() override;
    void draw() override;
    MyStr getType() const override;
};

class HardBrick : public Brick {
    int hp;
public:
    HardBrick(float x, float y);
    void hit() override;
    void draw() override;
    MyStr getType() const override;
};

class UnbreakableBrick : public Brick {
public:
    UnbreakableBrick(float x, float y);
    void hit() override;
    void draw() override;
    MyStr getType() const override;
};

class PowerBrick : public Brick {
    bool powerReleased;
public:
    PowerBrick(float x, float y);
    void hit() override;
    void draw() override;
    MyStr getType() const override;
    bool isPowerReleased() const;
};

#endif