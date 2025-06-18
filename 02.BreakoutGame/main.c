#include "paddle.h"
#include "brick.h"
#include "raylib.h"
#include "config.h"


Brick bricks[BRICK_ROWS][BRICK_COLS];
Color colors[] = {SKYBLUE, BLUE, YELLOW, ORANGE, BROWN};


void generateBricks() {
    for (int row = 0; row < BRICK_ROWS; row++) {
        for (int col = 0; col < BRICK_COLS; col++) {
            const double x = col * BRICK_W;
            const double y = row * BRICK_H + TOP_OFFSET;
            const Color color = colors[row % 5];
            const Brick brick = CreateBrick(x, y, color);
            bricks[row][col] = brick;
        }
    }
}

void handleBricks() {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            DrawBrick(&bricks[i][j]);
        }
    }
}


int main() {
    InitWindow(WIDTH, HEIGHT, "Breakout");

    Paddle paddle = CreatePaddle(WIDTH / 2 - PADDLE_W / 2, HEIGHT - PADDLE_H - 20);
    generateBricks();

    while (!WindowShouldClose()) {
        // Updating
        const float dt = GetFrameTime();
        UpdatePaddle(&paddle, dt);

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        DrawPaddle(&paddle);
        handleBricks();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}