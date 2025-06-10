#include "Ball.h"


Ball::Ball(float startX, float startY, float speedX, float speedY, float r)
    : x(startX), y(startY), velocityX(speedX), velocityY(speedY), radius(r) {
}

void Ball::update() {
    x += velocityX;
    y += velocityY;
}

void Ball::draw() {
    DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, RED);
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
