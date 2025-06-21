#include <stdlib.h>
#include <time.h>

#include "raylib.h"


const int WIDTH = 1200;
const int HEIGHT = 800;
const char* TITLE = "Bouncing Ball";
const int options[] = {-1, 1};
const int RADIUS = 20;
const int SPEED = 600;

int getRandom() {
    return options[rand() % 2];
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, TITLE);
    srand(time(NULL));

    Vector2 center = (Vector2) {WIDTH / 2, HEIGHT / 2};
    Vector2 direction = (Vector2){getRandom(), getRandom()};

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        float dt = GetFrameTime();

        DrawCircleV(center, RADIUS, DARKPURPLE);
        center.x += direction.x * SPEED * dt;
        center.y += direction.y * SPEED * dt;

        if (center.x - RADIUS <= 0) direction.x = 1;
        if (center.x + RADIUS >= WIDTH) direction.x = -1;
        if (center.y - RADIUS <= 0) direction.y = 1;
        if (center.y + RADIUS >= HEIGHT) direction.y = -1;

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
