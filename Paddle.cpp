#include "Paddle.h"
#include "raylib.h"
#include "Paddle.h"
#include "PowerUp.h"

Paddle::Paddle(int startX, int startY, int w, int h, int s)
    : x(startX), y(startY), width(w), height(h), speed(s) {
}

void Paddle::moveLeft() {
    x -= speed;
    if (x < 0) x = 0;
}

void Paddle::moveRight(int screenWidth) {
    x += speed;
    if (x + width > screenWidth) x = screenWidth - width;
}

void Paddle::draw() {
    DrawRectangle(x, y, width, height, BLUE);
}

Rectangle Paddle::getRect() const {
    return { (float)x, (float)y, (float)width, (float)height };
}

void Paddle::expand() {
    width += 40;
}

void Paddle::catchPowerUp(PowerUp* power) {

}
void Paddle::updatePosition(int newX, int newWidth) {
    x = newX;
    width = newWidth;
}