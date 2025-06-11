#pragma once
#include "raylib.h"
#include "Brick.h"
#include "Paddle.h"

class Ball {
private:
    float x;
    float y;
    float velocityX;
    float velocityY;
    float radius;
public:
    Ball();
    Ball(float startX, float startY, float speedX, float speedY, float r);
    void update();
    void draw() const;
    bool checkBrickCollision(Brick* brick);
    bool checkWallCollision(int screenWidth, int screenHeight);
    bool checkPaddleCollision(Paddle* paddle);
    float getX() const;
    float getY() const;
    float getVelocityX() const;
    float getVelocityY() const;
    void setVelocityX(float vx);
    void setVelocityY(float vy);
};
