#include "Ball.h"

Ball::Ball() : radius(10) {
    position = Position2D(400, 300);
    velocity = Position2D(3, -3);
}

void Ball::reset() {
    position = Position2D(400, 300);
    velocity = Position2D(3, -3);
}

void Ball::update( ) {
    position.x += velocity.x ;
    position.y += velocity.y ;

    if (position.x <= radius) {
        velocity.x *= -1;
    }
    if (position.x >= 800 - radius) {
        velocity.x *= -1;
    }
    if (position.y <= radius) {
        velocity.y *= -1;
    }
}

void Ball::draw() {
    DrawCircle(position.x, position.y, radius, RAYWHITE);
}

bool Ball::checkCollision(Rectangle rect) {
    Rectangle ballRect = {
        position.x - radius,
        position.y - radius,
        radius * 2,
        radius * 2
    };

    if (CheckCollisionRecs(ballRect, rect)) {

        if (position.y < rect.y || position.y > rect.y + rect.height) {
            velocity.y *= -1;
        }
        else {
            velocity.x *= -1;
        }
        return true;
    }
    return false;
}

bool Ball::isBelowScreen() {
    if (position.y > 600) {
        return true;
    }
    return false;
}

Position2D& Ball::getPosition() { return position; }
Position2D& Ball::getVelocity() { return velocity; }
void Ball::setVelocity(Position2D newVel) { velocity = newVel; }