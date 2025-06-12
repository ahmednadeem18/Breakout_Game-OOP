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
    balls.push(Ball(400, 300, 2 + levelNumber, -2 - levelNumber, 8));

    int rows = 6;
    int cols = 10;
    int spacing = 10;
    int brickWidth = 71;
    int brickHeight = 30;
    int startX = 0;
    int startY = 50;

    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < cols; i++) {
            int x = startX + i * (brickWidth + spacing);
            int y = startY + j * (brickHeight + spacing);

            if (j == 0) bricks.push(new UnbreakableBrick(x, y, brickWidth, brickHeight));
            else if (i == 1 && j == 1) bricks.push(new PowerBrick(x, y, brickWidth, brickHeight, new ExpandPaddlePowerUp()));
            else if (i == 2 && j == 2) bricks.push(new PowerBrick(x, y, brickWidth, brickHeight, new MultiBallPowerUp()));
            else if (j % 2 == 0) bricks.push(new HardBrick(x, y, brickWidth, brickHeight));
            else  bricks.push(new NormalBrick(x, y, brickWidth, brickHeight));
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
                        bricks.delete_at(j);
                        j--;
                        continue;
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
    for (int i = 0; i < bricks.size(); i++)
    {
        bricks.at(i)->draw();
    }
    for (int i = 0; i < balls.size(); i++) {
        balls.at(i).draw();
    }
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
const Paddle* Level::getPaddle() const {
    return paddle;
}
const MyVector<Ball>& Level::getBalls() const {
    return balls;
}
const MyVector<Brick*>& Level::getBricks() const {
    return bricks;
}