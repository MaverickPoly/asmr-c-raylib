#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "raylib.h"
#include "config.h"


Dino dino;
Cactus cactus[500];
size_t size = 0;
bool gameOver = false;

void DrawGround()
{
    float y = GROUND_Y + 5;
    Vector2 startPos = (Vector2){0, y};
    Vector2 endPos = (Vector2){WIDTH, y};
    DrawLineBezier(startPos, endPos, 4, BLACK);
}

int getRandomNumber(int a, int b) {
    return (rand() % (b - a + 1)) + a;
}

void SpawnCactus() {
    float x = getRandomNumber(WIDTH, WIDTH + 200);
    Cactus c = CreateCactus(x);
    cactus[size] = c;
    size++;
}

void HandleCactus(float dt, float speed) {
    Rectangle dinoRect = (Rectangle){dino.position.x, dino.position.y, DINO_W, DINO_H};
    // Drawing
    for (int i = 0; i < size; i++) {
        Cactus* c = &cactus[i];
        if (c->active) {
            UpdateCactus(c, dt, speed);
            Rectangle cRect = (Rectangle) {c->position.x, c->position.y, CACTUS_W, CACTUS_H};

            if (CheckCollisionRecs(dinoRect, cRect)) {
                gameOver = true;
            }
            DrawCactus(c);
        }
    }
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Dino Runner");
    srand(time(NULL));
    dino = CreateDino();

    float lastSpawn = 0;
    float spawDuration = SPAWN_DURATION;
    float speed = CACTUS_SPEED;
    float score = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        if (!gameOver) {
            float dt = GetFrameTime();
            lastSpawn++;
            spawDuration -= dt * 20;
            speed += dt * 5;
            score += dt * 5;
            printf("Duration: %f, ", spawDuration);
            printf("Speed: %f\n", speed);
            if (lastSpawn >= spawDuration) {
                lastSpawn = 0;
                SpawnCactus();
            }

            DrawGround();

            UpdateDino(&dino, dt);
            DrawDino(&dino);

            HandleCactus(dt, speed);

            char scoreText[100];
            sprintf(scoreText, "Score: %.1f", score);
            DrawText(scoreText, 10, 10, 50, BLACK);
        }
        else {
            DrawText("Game over!", 600, 400, 60, BLACK);
            char scoreText[100];
            sprintf(scoreText, "Score: %.1f", score);
            DrawText(scoreText, 600, 500, 50, BLACK);
        }


        EndDrawing();
    }

    CloseWindow();

    return 0;
}
