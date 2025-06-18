#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"

#define LEN 100
#define SIZE 80
#define SPEED 500


typedef struct {
    Color color;
    Vector2 center;
    double radius;
} Circle;

Circle circles[LEN];
Color colors[] = {RED, BLUE, SKYBLUE, BROWN, BLACK, YELLOW, ORANGE, GREEN, PURPLE, GRAY, LIME, GOLD};
Camera2D camera;

int getRandomNumber(int a, int b) {
    return (rand() % (b - a + 1)) + a;
}

void CreateCircles() {
    for (int i = 0; i < LEN; i++) {
        Color color = colors[rand()  % 12];
        Vector2 center = (Vector2) {getRandomNumber(-2000, 2000), getRandomNumber(-2000, 2000)};
        double radius = getRandomNumber(30, 180);
        Circle circle = (Circle){color, center, radius};
        circles[i] = circle;
    }
}


void DisplayCircles() {
    for (int i = 0; i < LEN; i++) {
        Circle circle = circles[i];
        DrawCircle(circle.center.x, circle.center.y, circle.radius, circle.color);
    }
}

int main() {
    InitWindow(1500, 1000, "Camera Movement");
    srand(time(NULL));
    CreateCircles();

    Vector2 pos = (Vector2){1500 / 2 - SIZE / 2, 1000 / 2 - SIZE / 2};
    Vector2 direction = (Vector2){0, 0};

    camera = (Camera2D) {};
    camera.target = pos;
    camera.zoom = 1;
    camera.offset = (Vector2){1500 / 2 - SIZE / 2, 1000 / 2 - SIZE / 2};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        BeginMode2D(camera);

        DisplayCircles();

        float dt = GetFrameTime();
        direction.x = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
        direction.y = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);
        pos.x += direction.x * dt * SPEED;
        pos.y += direction.y * dt * SPEED;
        Vector2Normalize(direction);
        DrawRectangleV(pos, (Vector2){SIZE, SIZE}, BEIGE);
        camera.target = pos;

        if (IsKeyDown(KEY_W) && camera.zoom <= 3.0) {
            camera.zoom += 1 * dt;
        }
        if (IsKeyDown(KEY_S) && camera.zoom >= 0.5) {
            camera.zoom -= 1 * dt;
        }

        EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}