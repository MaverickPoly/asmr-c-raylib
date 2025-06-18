#include "config.h"
#include "cube.h"
#include "raylib.h"

int main() {
    InitWindow(WIDTH, HEIGHT, "Flappy Cube");

    Cube cube = CreateCube();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        UpdateFlappyCube(&cube);
        DrawFlappyCube(&cube);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
