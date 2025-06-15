#include "Game.h"
#include <raylib.h>
#include <ctime>
#include"MyStr.h"
Game::Game() : score(0), currentLevel(1), isGameOver(false),
levelComplete(false), isPaused(false), backgroundColor(DARKBLUE),
logger(Logger::getInstance()) {
    initAudio();
    logger.initialize("game_log.txt");
    generateLevel();
    balls.pushBack(Ball());
}

Game::~Game() {
    cleanupAudio();
    for (int i = 0; i < bricks.getSize(); i++) {
        delete bricks.at(i);
    }
    for (int i = 0; i < powerUps.getSize(); i++) {
        delete powerUps.at(i);
    }
    logger.cleanup();
}

void Game::generateLevel() {
    for (int i = 0; i < bricks.getSize(); i++) {
        delete bricks.at(i);
    }
    bricks.clear();
    levelComplete = false;

    if (currentLevel == 1) {
        backgroundColor = DARKBLUE;
    }
    else if (currentLevel == 2) {
        backgroundColor = DARKGREEN;
    }
    else {
        backgroundColor = BLACK;
    }

    int rows = 4;
    if (currentLevel != 1) {
        rows = 6;
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < 10; col++) {
            float x = 60 + col * 65;
            float y = 50 + row * 25;

            int randomValue = GetRandomValue(0, 100);

            if (randomValue < 50) {
                bricks.pushBack(new NormalBrick(x, y));
            }
            else if (randomValue < 75) {
                bricks.pushBack(new HardBrick(x, y));
            }
            else if (randomValue < 90) {
                bricks.pushBack(new UnbreakableBrick(x, y));
            }
            else {
                bricks.pushBack(new PowerBrick(x, y));
            }
        }
    }

    MyStr logMsg = MyStr("Generated level ") + MyStr(currentLevel);
    logger.writeError(logMsg);
}

void Game::checkCollisions() {
    for (int i = 0; i < balls.getSize(); i++) {
        if (balls.at(i).checkCollision(paddle.getRectangle())) {
            PlaySound(paddleSound);
            balls.at(i).setVelocity(Position2D(
                balls.at(i).getVelocity().x,
                -abs(balls.at(i).getVelocity().y)
            ));
        }
    }

    for (int i = 0; i < bricks.getSize(); i++) {
        if (bricks.at(i)->getIsDestroyed()) {
            continue;
        }

        for (int j = 0; j < balls.getSize(); j++) {
            if (balls.at(j).checkCollision(bricks.at(i)->getRectangle())) {
                PlaySound(brickSound);
                bricks.at(i)->hit();

                if (bricks.at(i)->getType() == MyStr("Power")) {
                    PowerBrick* powerBrick = dynamic_cast<PowerBrick*>(bricks.at(i));
                    if (powerBrick && powerBrick->isPowerReleased()) {
                        if (GetRandomValue(0, 1) == 0) {
                            powerUps.pushBack(new MultiBallPowerUp(
                                bricks.at(i)->getRectangle().x,
                                bricks.at(i)->getRectangle().y
                            ));
                        }
                        else {
                            powerUps.pushBack(new PaddleSizePowerUp(
                                bricks.at(i)->getRectangle().x,
                                bricks.at(i)->getRectangle().y
                            ));
                        }
                    }
                }

                if (bricks.at(i)->getType() != MyStr("Unbreakable")) {
                    score += 10;
                }

                break;
            }
        }
    }

    for (int i = 0; i < powerUps.getSize(); i++) {
        if (!powerUps.at(i)->getIsActive() &&
            powerUps.at(i)->checkPaddleCollision(paddle.getRectangle())) {
            PlaySound(powerupSound);
            powerUps.at(i)->applyEffect(paddle, balls);
        }
    }
}

void Game::checkGameState() {
    for (int i = 0; i < balls.getSize(); i++) {
        if (balls.at(i).isBelowScreen()) {
            balls.removeAt(i);
            i--;
        }
    }

    if (balls.isEmpty() && !levelComplete) {
        isGameOver = true;
        logger.writeError(MyStr("Game Over - No balls left"));
    }

    bool flag = true;
    for (int i = 0; i < bricks.getSize(); i++) {
        if (!bricks.at(i)->getIsDestroyed() && bricks.at(i)->getType() != MyStr("Unbreakable")) {
            flag = false;
            break;
        }
    }

    if (flag && !levelComplete) {
        levelComplete = true;
        logger.writeError(MyStr("Level ") + MyStr(currentLevel) + MyStr(" completed"));

        if (currentLevel < 2) {
            currentLevel++;
            balls.clear();
            balls.pushBack(Ball());
            paddle.resetSize();
            powerUps.clear();
            generateLevel();
        }
        else {
            isGameOver = true;
            logger.writeError(MyStr("Game Won!"));
        }
    }
}

void Game::cleanPowerUps() {
    for (int i = 0; i < powerUps.getSize(); i++) {
        if (powerUps.at(i)->getIsActive() || powerUps.at(i)->getRectangle().y > 600) {
            delete powerUps.at(i);
            powerUps.removeAt(i);
            i--;
        }
    }
}

void Game::resetGame() {
    for (int i = 0; i < bricks.getSize(); i++) {
        delete bricks.at(i);
    }
    bricks.clear();

    for (int i = 0; i < powerUps.getSize(); i++) {
        delete powerUps.at(i);
    }
    powerUps.clear();
    balls.clear();
    score = 0;
    currentLevel = 1;
    isGameOver = false;
    levelComplete = false;
    isPaused = false;
    backgroundColor = DARKBLUE;

    generateLevel();
    balls.pushBack(Ball());
    paddle.resetSize();

    logger.writeError(MyStr("Game reset"));
}

void Game::update( ) {
    if (isGameOver) {
        if (IsKeyPressed(KEY_SPACE)) {
            resetGame();
        }
        return;
    }

    if (IsKeyPressed(KEY_P)) {
        isPaused = !isPaused;
        if (isPaused) {
            logger.writeError(MyStr("Game paused"));
        }
        else {
            logger.writeError(MyStr("Game resumed"));
        }
    }

    if (isPaused) {
        return;
    }

    paddle.update();

    for (int i = 0; i < balls.getSize(); i++) {
        balls.at(i).update();
    }

    for (int i = 0; i < powerUps.getSize(); i++) {
        powerUps.at(i)->update();
    }

    checkCollisions();
    checkGameState();
    cleanPowerUps();
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(backgroundColor);

    DrawText(TextFormat("Score: %d", score), 600, 10, 20, WHITE);
    DrawText(TextFormat("Level: %d", currentLevel), 40, 10, 20, WHITE);

    if (paddle.getHasPowerUp()) {
        float timeLeft = paddle.getPowerUpTimeLeft();
        const char* powerText = TextFormat("Power: %.1f", timeLeft);

        DrawText(powerText, 300, 10, 20, GREEN);
    }

    paddle.draw();

    for (int i = 0; i < balls.getSize(); i++) {
        balls.at(i).draw();
    }

    for (int i = 0; i < bricks.getSize(); i++) {
        if (!bricks.at(i)->getIsDestroyed()) {
            bricks.at(i)->draw();
        }
    }

    for (int i = 0; i < powerUps.getSize(); i++) {
        if (!powerUps.at(i)->getIsActive()) {
            powerUps.at(i)->draw();
        }
    }

    if (isGameOver) {
        if (currentLevel >= 2 && levelComplete) {
            DrawText("YOU WIN!", 350, 280, 40, GREEN);
        }
        else {
            DrawText("GAME OVER", 300, 280, 40, RED);
        }
        DrawText(TextFormat("Final Score: %d", score), 310, 330, 20, WHITE);
        DrawText("Press SPACE to restart", 300, 370, 20, WHITE);
    }

    if (isPaused) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{ 0, 0, 0, 128 });
        DrawText("PAUSED", 300, 250, 40, WHITE);
        DrawText("Press P to Resume", 300, 300, 20, WHITE);
    }

    EndDrawing();
}
void Game::initAudio() {
    InitAudioDevice();
    brickSound = LoadSound("sounds/brick.wav");
    paddleSound = LoadSound("sounds/paddle.wav");
    powerupSound = LoadSound("sounds/powerup.wav");
}
void Game::cleanupAudio() {
    UnloadSound(brickSound);
    UnloadSound(paddleSound);
    UnloadSound(powerupSound);
    CloseAudioDevice();
}
