#pragma once
#include <raylib.h>

class PowerUp;

class Paddle {
private:
    int x;
    int y;
    int width;
    int height;
    int speed;
public:
    Paddle(int startX, int startY, int w, int h, int s);
    void moveLeft();
    void moveRight(int screenWidth);
    void draw();
    Rectangle getRect() const;
    void expand();
    void catchPowerUp(PowerUp* power);
    void updatePosition(int newX, int newWidth);
};


