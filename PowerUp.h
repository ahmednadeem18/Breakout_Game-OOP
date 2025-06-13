#ifndef POWERUP_H
#define POWERUP_H

#include "MyStr.h"
#include <raylib.h>
#include <chrono>
#include"MyVector.h"
class PowerUp {
protected:
    Rectangle rectangle;
    bool isActive;
    float fallSpeed;

public:
    PowerUp(float x, float y) : isActive(false), fallSpeed(1) {
        rectangle = { x, y, 20, 20 };
    }

    virtual ~PowerUp() {}
    virtual void applyEffect(class Paddle& paddle, class MyVector<class Ball>& balls) = 0;
    virtual void draw() = 0;

    void update() {
        if (!isActive) {
            rectangle.y += fallSpeed ;
        }
    }

    bool checkPaddleCollision(Rectangle paddleRect) {
        return CheckCollisionRecs(rectangle, paddleRect);
    }

    bool getIsActive() const { return isActive; }
    Rectangle getRectangle() const { return rectangle; }
};

class PaddleSizePowerUp : public PowerUp {
public:
    PaddleSizePowerUp(float x, float y) : PowerUp(x, y) {}

    void applyEffect(Paddle& paddle, MyVector<Ball>& balls) override;
    void draw() override;
};

class MultiBallPowerUp : public PowerUp {
public:
    MultiBallPowerUp(float x, float y) : PowerUp(x, y) {}

    void applyEffect(Paddle& paddle, MyVector<Ball>& balls) override;
    void draw() override;
};

#endif