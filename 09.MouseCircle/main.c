#include "raylib.h";


// Constants
const int WIDTH = 1300, HEIGHT = 800;


int main() {
    InitWindow(WIDTH, HEIGHT, "Mouse Circle");

    Vector2 mousePosition = (Vector2) {0, 0};

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        const Vector2 pos = GetMousePosition();
        mousePosition.x = pos.x;
        mousePosition.y = pos.y;

        DrawCircle(mousePosition.x, mousePosition.y, 20, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
