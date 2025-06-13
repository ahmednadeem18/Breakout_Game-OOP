#include "Paddle.h"
#include <raylib.h>
#include <chrono>

Paddle::Paddle() : movementSpeed(6.5), originalWidth(100), currentWidth(100), maxWidth(200), hasPowerUp(false) {
    rectangle = { 370, 550, currentWidth, 20 };
}

void Paddle::update( ) {
    if (IsKeyDown(KEY_LEFT)) {
        rectangle.x -= movementSpeed ;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        rectangle.x += movementSpeed ;
    }

    if (rectangle.x < 0) {
        rectangle.x = 0;
    }
    if (rectangle.x > 800 - rectangle.width) {
        rectangle.x = 800 - rectangle.width;
    }

    if (hasPowerUp) {
        std::chrono::duration<float> elapsed = std::chrono::steady_clock::now() - powerUpTime;
        if (elapsed.count() >= 10) {
            resetSize();
        }
    }
}

void Paddle::draw() {
    DrawRectangleRec(rectangle, BLUE);
}

void Paddle::increaseSize() {
    if (currentWidth * 1.5f < maxWidth) {
        currentWidth = currentWidth * 1.5f;
    }
    else {
        currentWidth = maxWidth;
    }
    rectangle.width = currentWidth;
    powerUpTime = std::chrono::steady_clock::now();
    hasPowerUp = true;
}

void Paddle::resetSize() {
    currentWidth = originalWidth;
    rectangle.width = currentWidth;
    hasPowerUp = false;
}

Rectangle& Paddle::getRectangle() {
    return rectangle;
}

bool Paddle::getHasPowerUp() const { return hasPowerUp; }

float Paddle::getPowerUpTimeLeft() const {
    if (!hasPowerUp) {
        return 0;
    }
    std::chrono::duration<float> elapsed = std::chrono::steady_clock::now() - powerUpTime;
    return 10 - elapsed.count();
}