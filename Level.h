#pragma once
#include "MyVector.h"
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"

class Level {
private:
    MyVector<Brick*> bricks;
    MyVector<Ball> balls;
    Paddle* paddle;
    int number;
public:
    Level();
    ~Level();
    void load(int levelNumber);
    void update(int screenWidth, int screenHeight);
    void draw() const;
    bool isCleared() const;
    MyVector<Ball>& getBalls();
    MyVector<Brick*>& getBricks();
    Paddle* getPaddle();
    const Paddle* getPaddle() const;
    const MyVector<Brick*>& getBricks() const;
    const MyVector<Ball>& getBalls() const;
};
