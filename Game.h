#ifndef GAME_H
#define GAME_H

#include "MyVector.h"
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "PowerUp.h"
#include "Logger.h"
#include <raylib.h>

class Game {
private:
    MyVector<Ball> balls;
    MyVector<Brick*> bricks;
    MyVector<PowerUp*> powerUps;
    Paddle paddle;
    int score;
    int currentLevel;
    bool isGameOver;
    bool levelComplete;
    bool isPaused;
    Color backgroundColor;
    Logger& logger;
    Sound brickSound;
    Sound paddleSound;
    Sound powerupSound;

    void initAudio();
    void cleanupAudio();
    void generateLevel();
    void checkCollisions();
    void checkGameState();
    void cleanPowerUps();

public:
    Game();
    ~Game();
    void resetGame();
    void update( );
    void draw();
};

#endif