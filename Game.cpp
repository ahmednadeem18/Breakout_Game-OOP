#include "Game.h"
#include "raylib.h"
#include "SaveLoadManager.h"

Game::Game() : score(0), currentLevel(0), logger(Logger::getInstance()) {
    Level level;
    level.load(0);
    levels.push(level);
    logger.initialize(MyStr("log.txt"));
}

void Game::start(int screenWidth, int screenHeight) {
    InitWindow(screenWidth, screenHeight, "Breakout++");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        handleInput();
        update(screenWidth, screenHeight);
        BeginDrawing();
        ClearBackground(BLACK);
        draw();
        EndDrawing();
    }
    logger.cleanup();
    CloseWindow();
}

void Game::handleInput() {
    Paddle* paddle = levels.at(currentLevel).getPaddle();
    if (IsKeyDown(KEY_LEFT)) paddle->moveLeft();
    if (IsKeyDown(KEY_RIGHT)) paddle->moveRight(GetScreenWidth());
    if (IsKeyPressed(KEY_S)) saveGame(MyStr("save.dat"));
    if (IsKeyPressed(KEY_L)) loadGame(MyStr("save.dat"));
}

void Game::update(int screenWidth, int screenHeight) {
    levels.at(currentLevel).update(screenWidth, screenHeight);
    if (levels.at(currentLevel).isCleared()) {
        currentLevel++;
        Level next;
        next.load(currentLevel);
        levels.push(next);
    }
}

void Game::draw() const {
    levels.at(currentLevel).draw();
}
