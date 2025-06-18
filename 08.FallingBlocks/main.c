#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#include "config.h"

typedef struct {
    bool active;
    Vector2 pos;
    double speed;
    Color color;
} Block;

Block blocks[500];
size_t size = 0;
Color colors[] = {RED, GREEN, ORANGE, YELLOW, PINK, BROWN};
Vector2 blockSize = (Vector2){BLOCK_W, BLOCK_H};

int getRandomNumber(int a, int b) {
    return (rand() % (b - a + 1)) + a;
}

void CreateBlock() {
    double speed = getRandomNumber(100, 600);
    int x = getRandomNumber(0, WIDTH - BLOCK_W);
    int y = getRandomNumber(-200, -100);
    Color color = colors[rand() % 6];
    Block block = (Block) {.active = true, .pos = (Vector2){x, y}, .speed = speed, .color = color};
    blocks[size++] = block;
}


int main() {
    InitWindow(WIDTH, HEIGHT, "Catch Falling Blocks");
    srand(time(NULL));

    // Paddle
    Vector2 paddlePos = (Vector2) {WIDTH / 2 - PADDLE_W / 2, HEIGHT - PADDLE_H - 30};
    int score = 0;

    // Blocks
    float lastSpawn = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        float dt = GetFrameTime();

        // Paddle
        if (IsKeyDown(KEY_LEFT)) paddlePos.x -= PADDLE_SPEED * dt;
        if (IsKeyDown(KEY_RIGHT)) paddlePos.x += PADDLE_SPEED * dt;

        DrawRectangleV(paddlePos, (Vector2){PADDLE_W, PADDLE_H}, VIOLET);
        Rectangle paddleRect = (Rectangle){paddlePos.x, paddlePos.y, PADDLE_W, PADDLE_H};

        // Blocks
        for (size_t i = 0; i < size; i++) {
            Block* block = &blocks[i];
            if (block->active) {
                block->pos.y += block->speed * dt;
                if (block->pos.y > HEIGHT) {
                    block->active = false;
                }
                DrawRectangleV(block->pos, blockSize, block->color);
            }
            Rectangle blockRect = (Rectangle){block->pos.x, block->pos.y, BLOCK_W, BLOCK_H};
            if (CheckCollisionRecs(blockRect, paddleRect) && block->active) {
                block->active = false;
                score++;
            }
        }
        lastSpawn += dt;
        if (lastSpawn >= SPAWN_DURATION) {
            CreateBlock();
            lastSpawn = 0;
        }

        // Texts
        char scoreText[100];
        sprintf(scoreText, "Score: %d", score);
        DrawText(scoreText, 10, HEIGHT - 50, 50, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
