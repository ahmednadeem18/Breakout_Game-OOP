#include "Game.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Brick Breaker");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.update();
        game.draw();
    }

    CloseWindow();
    return 0;
}