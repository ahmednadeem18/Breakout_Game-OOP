#pragma once
#include "Paddle.h"
#include "MyVector.h"
#include "Ball.h"

class PowerUp {
public:
    virtual void activate(Paddle* paddle, MyVector<Ball>* balls) = 0;
    virtual ~PowerUp() {}
};

class ExpandPaddlePowerUp : public PowerUp {
public:
    void activate(Paddle* paddle, MyVector<Ball>* balls) override {
        paddle->expand();
    }
};

class MultiBallPowerUp : public PowerUp {
public:
    void activate(Paddle* paddle, MyVector<Ball>* balls) override {
        if (balls->size() > 0) {
            Ball b = balls->at(0);
            b.setVelocityX(-b.getVelocityX());
            b.setVelocityY(-b.getVelocityY());
            balls->push(b);
        }
    }
};

