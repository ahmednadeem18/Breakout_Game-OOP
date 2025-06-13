#ifndef POSITION2D_H
#define POSITION2D_H

class Position2D {
public:
    float x;
    float y;

    Position2D();
    Position2D(float xPos, float yPos);
    Position2D& operator=(const Position2D& other);
};

#endif