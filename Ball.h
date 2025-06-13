#ifndef BALL_H
#define BALL_H

#include "Position2D.h"
#include <raylib.h>

class Ball {
private:
    Position2D position;
    Position2D velocity;
    float radius;

public:
    Ball();
    void reset();
    void update( );
    void draw();
    bool checkCollision(Rectangle rect);
    bool isBelowScreen();
    Position2D& getPosition();
    Position2D& getVelocity();
    void setVelocity(Position2D newVel);
};

#endif