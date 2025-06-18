#include "raylib.h";
#include "config.h"


void DrawBackground() {

}

int main() {
    InitWindow(WIDTH, HEIGHT, "Snake Game");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }

    CloseWindow();
}