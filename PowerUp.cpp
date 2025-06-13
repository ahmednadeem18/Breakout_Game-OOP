#include "PowerUp.h"
#include "Paddle.h"
#include "Ball.h"

void PaddleSizePowerUp::applyEffect(Paddle& paddle, MyVector<Ball>& balls) {
    paddle.increaseSize();
    isActive = true;
}

void PaddleSizePowerUp::draw() {
    DrawRectangleRec(rectangle, GREEN);
}

void MultiBallPowerUp::applyEffect(Paddle& paddle, MyVector<Ball>& balls) {
    if (balls.getSize() > 0) {
        Ball newBall = balls.at(0);
        newBall.setVelocity(Position2D(
            newBall.getVelocity().x * -1,
            newBall.getVelocity().y
        ));
        balls.pushBack(newBall);
    }
    isActive = true;
}

void MultiBallPowerUp::draw() {
    DrawRectangleRec(rectangle, SKYBLUE);
}