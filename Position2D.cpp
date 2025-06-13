#include "Position2D.h"

Position2D::Position2D() : x(0), y(0) {}
Position2D::Position2D(float xPos, float yPos) : x(xPos), y(yPos) {}

Position2D& Position2D::operator=(const Position2D& other) {
    x = other.x;
    y = other.y;
    return *this;
}