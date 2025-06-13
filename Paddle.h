#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>
#include <chrono>

class Paddle {
private:
    Rectangle rectangle;
    float movementSpeed;
    float originalWidth;
    float currentWidth;
    float maxWidth;
    std::chrono::steady_clock::time_point powerUpTime;
    bool hasPowerUp;

public:
    Paddle();
    void update( );
    void draw();
    void increaseSize();
    void resetSize();
    Rectangle& getRectangle();
    bool getHasPowerUp() const;
    float getPowerUpTimeLeft() const;
};

#endif