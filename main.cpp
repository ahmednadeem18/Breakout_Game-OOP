#include "raylib.h"
#include "Level.h"
#include "Logger.h"
#include "SaveLoadManager.h"
#include "MyStr.h"
#include "MyVector.h"

Level currentLevel;
int currentLevelIndex = 0;
Logger& logger = Logger::getInstance();

void handleInput() {
    Paddle* paddle = currentLevel.getPaddle();
    if (IsKeyDown(KEY_LEFT)) paddle->moveLeft();
    if (IsKeyDown(KEY_RIGHT)) paddle->moveRight(GetScreenWidth());
    if (IsKeyPressed(KEY_S)) SaveLoadManager::saveLevel(currentLevel, "save.bin");
    if (IsKeyPressed(KEY_L)) SaveLoadManager::loadLevel(currentLevel, "save.bin");
}

void update(int screenWidth, int screenHeight) {
    currentLevel.update(screenWidth, screenHeight);

    if (currentLevel.getBalls().size() == 0) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("GAME OVER", 300, 250, 40, RED);
        EndDrawing();
        double start = GetTime();
        while (GetTime() - start < 2.0) {}
        CloseWindow();
    }

    if (currentLevel.isCleared()) {
        currentLevelIndex++;
        Level next;
        next.load(currentLevelIndex);
        currentLevel = next;
    }
}

void draw() {
    currentLevel.draw();
}

int main() {
    InitWindow(800, 600, "BreakOut");
    SetTargetFPS(60);
    logger.initialize("log.txt");

    currentLevel.load(0);

    while (!WindowShouldClose()) {
        handleInput();
        update(800, 600);

        BeginDrawing();
        ClearBackground(BLACK);
        draw();
        EndDrawing();
    }

    logger.cleanup();
    CloseWindow();
    return 0;
}
