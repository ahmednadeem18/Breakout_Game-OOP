#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "raylib.h"
Ball::Ball() : x(0), y(0), velocityX(0), velocityY(0), radius(5) {}

Ball::Ball(float startX, float startY, float speedX, float speedY, float r)
    : x(startX), y(startY), velocityX(speedX), velocityY(speedY), radius(r) {
}

void Ball::update() {
    x += velocityX;
    y += velocityY;
}

void Ball::draw() {
    DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, WHITE);
}
bool Ball::checkWallCollision(int screenWidth, int screenHeight) {
    if (x - radius <= 0 || x + radius >= screenWidth) {
        velocityX *= -1;
        return true;
    }
    if (y - radius <= 0) {
        velocityY *= -1;
        return true;
    }
    return false;
}

bool Ball::checkPaddleCollision(Paddle* paddle) {
    Rectangle paddleRect = paddle->getRect();
    Rectangle ballRect = { x - radius, y - radius, radius * 2, radius * 2 };
    if (CheckCollisionRecs(ballRect, paddleRect)) {
        velocityY *= -1;
        return true;
    }
    return false;
}

bool Ball::checkBrickCollision(Brick* brick) {
    Rectangle brickRect = brick->getRect();
    Rectangle ballRect = { x - radius, y - radius, radius * 2, radius * 2 };
    if (CheckCollisionRecs(ballRect, brickRect)) {
        velocityY *= -1;
        return true;
    }
    return false;
}
float Ball::getX() const {
    return x;
}

float Ball::getY() const {
    return y;
}

float Ball::getVelocityX() const {
    return velocityX;
}

float Ball::getVelocityY() const {
    return velocityY;
}

void Ball::setVelocityX(float vx) {
    velocityX = vx;
}

void Ball::setVelocityY(float vy) {
    velocityY = vy;
}
