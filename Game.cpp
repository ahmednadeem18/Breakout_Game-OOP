#include "Game.h"
#include <raylib.h>
#include "SaveLoadManager.h"

Game::Game() : score(0), currentLevel(0), logger(Logger::getInstance()) {
    Level level;
    
    levels.push(level);
    levels[0].load(0);
    //logger.initialize("log.txt");
}

void Game::start(int screenWidth, int screenHeight) {
    /*InitWindow(800, 600, "Game");*/
    InitWindow(screenWidth, screenHeight, "BreakOut");
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
    if (IsKeyPressed(KEY_S)) saveGame();
    if (IsKeyPressed(KEY_L)) loadGame();
}

void Game::update(int screenWidth, int screenHeight) {
    levels.at(currentLevel).update(screenWidth, screenHeight);
    if (levels.at(currentLevel).getBalls().size() == 0) {
        CloseWindow();  
        return;
    }
    if (levels.at(currentLevel).isCleared()) {
        currentLevel++;
        Level next;
        levels.push(next);
        int s = levels.size();
        levels[s - 1].load(currentLevel);
    }
}

void Game::draw() const {
    levels.at(currentLevel).draw();
}

void Game::loadGame() {
    SaveLoadManager::loadLevel(levels.at(currentLevel), "data.bin");
    logger.writeError(MyStr("Game state loaded."));
}

void Game::saveGame(const MyStr& filename) {
    SaveLoadManager::saveLevel(levels.at(currentLevel), "data.bin");
    logger.writeError(MyStr("Game state saved."));
}