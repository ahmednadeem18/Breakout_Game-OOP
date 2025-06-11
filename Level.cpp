#include "Level.h"
#include "NormalBrick.h"
#include "HardBrick.h"
#include "UnbreakableBrick.h"
#include "PowerBrick.h"
#include "PowerUp.h"

Level::Level() {
    paddle = new Paddle(300, 450, 100, 20, 8);
}

Level::~Level() {
    for (int i = 0; i < bricks.size(); i++) delete bricks.at(i);
    delete paddle;
}

void Level::load(int levelNumber) {
    number = levelNumber;
    bricks.clear();
    balls.clear();
    balls.push(Ball(400, 300, 4 + levelNumber, -4 - levelNumber, 8));
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            int x = 100 + i * 70;
            int y = 50 + j * 35;
            if (j == 0) bricks.push(new UnbreakableBrick(x, y, 60, 25));
            else if (j == 1) bricks.push(new PowerBrick(x, y, 60, 25, new ExpandPaddlePowerUp()));
            else if (j == 2) bricks.push(new PowerBrick(x, y, 60, 25, new MultiBallPowerUp()));
            else if (j % 2 == 0) bricks.push(new NormalBrick(x, y, 60, 25));
            else bricks.push(new HardBrick(x, y, 60, 25));
        }
    }
}

void Level::update(int screenWidth, int screenHeight) {
    for (int i = 0; i < balls.size(); i++) {
        balls.at(i).update();
        balls.at(i).checkWallCollision(screenWidth, screenHeight);
        if (balls.at(i).getY() <= screenHeight) {
            balls.at(i).checkPaddleCollision(paddle);
            for (int j = 0; j < bricks.size(); j++) {
                if (balls.at(i).checkBrickCollision(bricks.at(j))) {
                    bricks.at(j)->hit();
                    if (bricks.at(j)->isDestroyed()) {
                        if (bricks.at(j)->isPowerBrick()) {
                            PowerBrick* pb = static_cast<PowerBrick*>(bricks.at(j));
                            pb->releasePowerUp()->activate(paddle, &balls);
                        }
                        delete bricks.at(j);
                        balls.delete_at(i);
                        j--;
                    }
                    break;
                }
            }
        }
        else {
            balls.delete_at(i);
            i--;
        }
    }
}

void Level::draw() const {
    for (int i = 0; i < bricks.size(); i++) bricks.at(i)->draw();
    for (int i = 0; i < balls.size(); i++) balls.at(i).draw();
    paddle->draw();
}

bool Level::isCleared() const {
    for (int i = 0; i < bricks.size(); i++) {
        if (!bricks.at(i)->isDestroyed()) {
            if (!dynamic_cast<UnbreakableBrick*>(bricks.at(i)))
                return false;
        }
    }
    return true;
}

MyVector<Ball>& Level::getBalls() {
    return balls;
}

MyVector<Brick*>& Level::getBricks() {
    return bricks;
}

Paddle* Level::getPaddle() {
    return paddle;
}
