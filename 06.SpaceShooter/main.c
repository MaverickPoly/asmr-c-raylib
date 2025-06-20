#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "raylib.h"
#include "config.h"

// Stars
Texture2D starTexture;
Vector2 stars[STARS_NUM];
size_t starsCount = 0;

// Rocket
Rocket rocket;
Laser lasers[500];
size_t lasersCount = 0;
double lastShoot;


int getRandomNumber(int a, int b) {
    return (rand() % (b - a + 1)) + a;
}

void GenerateStars() {
    for (int i = 0; i < STARS_NUM; i++) {
        Vector2 position = (Vector2){getRandomNumber(-10, WIDTH - 30), getRandomNumber(-10, HEIGHT - 30)};
        stars[starsCount++] = position;
    }
}

void DrawBackground() {
    ClearBackground(BLACK);
    for (int i = 0; i < STARS_NUM; i++) {
        DrawTexture(starTexture, stars[i].x, stars[i].y, WHITE);
    }
}

void GenerateLaser() {
    float x = rocket.rect.x + ROCKET_W / 2;
    float y = rocket.rect.y;

    Laser laser = CreateLaser(x, y);
    lasers[lasersCount++] = laser;
}

void HandleRocket(float dt) {
    UpdateRocket(&rocket, dt);
    DrawRocket(&rocket);

    double currentTime = GetTime();
    if (IsKeyPressed(KEY_SPACE) && (currentTime - lastShoot) >= SHOOT_RELOAD) {
        GenerateLaser();
        lastShoot = currentTime;
    }
}

void HandleLasers(float dt) {
    for (int i = 0; i < lasersCount; i++) {
        Laser *laser = &lasers[i];
        if (laser->active) {
            UpdateLaser(laser, dt);
            DrawLaser(laser);
        }
    }
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Space Shooter");
    srand(time(NULL));
    GenerateStars();
    starTexture = LoadTexture("..\\06.SpaceShooter\\images\\star.png");

    rocket = CreateRocket();
    lastShoot = GetTime();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        BeginDrawing();
        DrawBackground();

        HandleRocket(dt);
        HandleLasers(dt);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
