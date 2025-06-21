#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "raylib.h"
#include "config.h"


Sound explosionSound;
Sound gameMusic;
Sound laserSound;
int score = 0;
bool gameOver = false;
Font font;

// Stars
Texture2D starTexture;
Vector2 stars[STARS_NUM];
size_t starsCount = 0;

// Rocket
Rocket rocket;
Laser lasers[500];
size_t lasersCount = 0;
double lastShoot;

// Meteors
Meteor meteors[500];
size_t meteorsCount = 0;
double lastMeteor;

double getRandomNumber(double a, double b) {
    return (rand() % (int)(b - a + 1)) + a;
}

void GenerateStars() {
    for (int i = 0; i < STARS_NUM; i++) {
        Vector2 position = (Vector2){(float)getRandomNumber(-10, WIDTH - 30), (float)getRandomNumber(-10, HEIGHT - 30)};
        stars[starsCount++] = position;
    }
}

void DrawBackground() {
    ClearBackground(BLACK);
    for (int i = 0; i < STARS_NUM; i++) {
        DrawTexture(starTexture, (int)stars[i].x, (int)stars[i].y, WHITE);
    }
}

void GenerateLaser() {
    float x = rocket.rect.x + ROCKET_W / 2 - LASER_W / 2;
    float y = rocket.rect.y;

    Laser laser = CreateLaser(x, y);
    lasers[lasersCount++] = laser;
    PlaySound(laserSound);
}

void GenerateMeteor() {
    int rotation = (int)getRandomNumber(0, 360);
    int x = (int)getRandomNumber(100, WIDTH - 100);
    int y = (int)getRandomNumber(-200, -100);
    int speed = (int)getRandomNumber(400, 500);
    Vector2 direction = (Vector2){(float)getRandomNumber(-0.7, 0.7), 1};
    Meteor meteor = CreateMeteor(rotation, (float)x, (float)y, (float)speed, direction);
    meteors[meteorsCount++] = meteor;
}

void HandleRocket(float dt) {
    UpdateRocket(&rocket, dt);
    DrawRocket(&rocket);

    double currentTime = GetTime();
    if (IsKeyPressed(KEY_SPACE) && (currentTime - lastShoot) >= SHOOT_RELOAD) {
        GenerateLaser();
        lastShoot = currentTime;
    }

    score = (int)(GetTime() *  10);
}

void HandleLasers(float dt) {
    for (int i = 0; i < lasersCount; i++) {
        Laser *laser = &lasers[i];
        if (laser->active) {
            UpdateLaser(laser, dt);
            DrawLaser(laser);

            for (int j = 0; j < meteorsCount; j++) {
                Meteor *m = &meteors[j];
                if (!m->active) continue;
                if (CheckCollisionRecs(laser->rect, m->rectangle)) {
                    m->active = false;
                    laser->active = false;
                    PlaySound(explosionSound);
                }
            }
        }
    }
}

void HandleMeteors(float dt) {
    for (int i = 0; i < meteorsCount; i++) {
        Meteor *meteor = &meteors[i];
        if (meteor->active) {
            UpdateMeteor(meteor, dt);
            DrawMeteor(meteor);

            if (CheckCollisionRecs(rocket.rect, meteor->rectangle)) {
                gameOver = true;
            }
        }
    }

    // Spawn Meteor
    double currentTime = GetTime();
    if (currentTime - lastMeteor >= METEOR_SPAWN_TIME) {
        GenerateMeteor();
        lastMeteor = currentTime;
    }
}

void DrawTexts() {
    // Score
    char scoreText[100];
    sprintf(scoreText, "%d", score);
    DrawTextEx(font, scoreText, (Vector2){WIDTH / 2 - 50, 100}, 80, 2, WHITE);
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Space Shooter");
    InitAudioDevice();

    explosionSound = LoadSound("..\\06.SpaceShooter\\audio\\explosion.wav");
    gameMusic = LoadSound("..\\06.SpaceShooter\\audio\\game_music.wav");
    laserSound = LoadSound("..\\06.SpaceShooter\\audio\\laser.wav");

    srand(time(NULL));
    font = LoadFont("..\\06.SpaceShooter\\images\\Oxanium-Bold.ttf");
    GenerateStars();
    starTexture = LoadTexture("..\\06.SpaceShooter\\images\\star.png");

    rocket = CreateRocket();
    lastShoot = GetTime();
    lastMeteor = GetTime();

    PlaySound(gameMusic);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (gameOver) break;

        BeginDrawing();
        DrawBackground();

        HandleRocket(dt);
        HandleLasers(dt);
        HandleMeteors(dt);
        DrawTexts();

        EndDrawing();
    }

    UnloadSound(explosionSound);
    UnloadSound(gameMusic);
    UnloadSound(laserSound);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
