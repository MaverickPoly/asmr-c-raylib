#include <stdlib.h>
#include <time.h>

#include "ball.h"
#include "paddle.h"
#include "brick.h"
#include "raylib.h"
#include "config.h"


Brick** bricks;
Color colors[] = {SKYBLUE, BLUE, YELLOW, ORANGE, BROWN};
float directionOptions[2] = {-1.0, 1.0};
Paddle paddle;
Ball ball;
int lives = 3;
int gameOver = 0;


void generateBricks() {
    bricks = malloc(BRICK_ROWS * sizeof(Brick*));
    for (int i = 0; i < BRICK_ROWS; i++) {
        bricks[i] = malloc(BRICK_COLS * sizeof(Brick));
    }

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
            Brick brick = bricks[i][j];
            if (brick.active) {
                DrawBrick(&brick);
            }
        }
    }

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            Brick* brick = &bricks[i][j];
            if (!brick->active) continue;
            if (CheckCollisionCircleRec(ball.position, BALL_RADIUS, brick->rect)) {
                brick->active = 0;
                ball.direction.y *= -1;
            }
        }
    }

    bool reset = true;
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            if (bricks[i][j].active) {
                reset = false;
                goto func_end;
            }
        }
    }
    func_end:
    if (reset) {
        gameOver = 1;
    }
}

void resetBall() {
    ball.position.x = WIDTH / 2;
    ball.position.y = HEIGHT / 2;
    ball.direction.x = directionOptions[rand() % 2];
    ball.direction.y = -1;
}

void FreeBricksMemory() {
    for (int i = 0; i < BRICK_ROWS; i++) {
        free(bricks[i]);
    }
    free(bricks);
}

void drawLives() {
    char text[100];
    itoa(lives, text, 10);
    DrawText("Lives: ", 10, 10, 40, GREEN);
    DrawText(text, 150, 10, 40, WHITE);
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Breakout");

    srand(time(NULL));

    paddle = CreatePaddle(WIDTH / 2 - PADDLE_W / 2, HEIGHT - PADDLE_H - 20);
    ball = CreateBall((Vector2){directionOptions[rand() % 2], -1});
    generateBricks();

    while (!WindowShouldClose()) {
        // Updating
        if (!gameOver) {
            const float dt = GetFrameTime();
            UpdatePaddle(&paddle, dt);
            const int belowBottom = UpdateBall(&ball, dt, &paddle);
            if (belowBottom) {
                resetBall();
                lives--;

                if (lives <= 0) {
                    gameOver = 1;
                }
            }
        } else {
            if (lives > 0) {
                DrawText("Game over! You won!", WIDTH / 2 - 200, HEIGHT / 2 - 100, 42, WHITE);
            } else {
                DrawText("Game over! You lost!", WIDTH / 2 - 200, HEIGHT / 2 - 100, 42, WHITE);
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        DrawPaddle(&paddle);
        handleBricks();
        DrawBall(&ball);
        drawLives();

        EndDrawing();
    }
    CloseWindow();

    FreeBricksMemory();

    return 0;
}