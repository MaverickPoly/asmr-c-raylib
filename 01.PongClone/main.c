#include <stdio.h>

#include "raylib.h"
#include <time.h>
#include <stdlib.h>

// Constants
#define WIDTH 1400.0
#define HEIGHT 800.0
#define OFFSET 30
#define PADDLE_W 15.0
#define PADDLE_H 180.0
#define PADDLE_SPEED 700
#define BALL_RADIUS 20
#define BALL_SPEED 700


int left_score = 0;
int right_score = 0;
const int direction_choices[2] = {-1, 1};

// Paddles
// Vector2 paddle1_pos = Vector2{.x = OFFSET, .y = HEIGHT / 2 - PADDLE_H / 2};
Vector2 paddle1_pos = (Vector2){OFFSET, HEIGHT / 2 - PADDLE_H / 2};
// Vector2 paddle2_pos = Vector2{.x = WIDTH - OFFSET, .y = HEIGHT / 2 - PADDLE_H / 2};
Vector2 paddle2_pos = (Vector2){ WIDTH - OFFSET - PADDLE_W, HEIGHT / 2 - PADDLE_H / 2};

void handlePaddle(Vector2* paddle_pos, const int isLeft) {
    DrawRectangle((int)paddle_pos->x, (int)paddle_pos->y, PADDLE_W, PADDLE_H, GRAY);

    const float dt = GetFrameTime();
    if (isLeft) {
        if (IsKeyDown(KEY_W)) {
            paddle_pos->y -= PADDLE_SPEED * dt;
        } else if (IsKeyDown(KEY_S)) {
            paddle_pos->y += PADDLE_SPEED * dt;
        }
    } else {
        if (IsKeyDown(KEY_UP)) {
            paddle_pos->y -= PADDLE_SPEED * dt;
        } else if (IsKeyDown(KEY_DOWN)) {
            paddle_pos->y += PADDLE_SPEED * dt;
        }
    }

    if (paddle_pos->y <= 0) {
        paddle_pos->y = 0;
    } else if (paddle_pos->y + PADDLE_H >= HEIGHT) {
        paddle_pos->y = HEIGHT - PADDLE_H;
    }
}

void resetBall(Vector2* ball_pos, Vector2 *ball_direction) {
    ball_pos->x = WIDTH / 2;
    ball_pos->y = HEIGHT / 2;

    *ball_direction = (Vector2){direction_choices[rand() % 2], direction_choices[rand() % 2]};
}

void handleBall(Vector2* ball_pos, Vector2 *ball_direction) {
    // Draw
    DrawCircle((int)ball_pos->x, (int)ball_pos->y, BALL_RADIUS, RED);

    // Move
    const float dt = GetFrameTime();
    ball_pos->x += ball_direction->x * dt * BALL_SPEED;
    ball_pos->y += ball_direction->y * dt * BALL_SPEED;

    // Collisions with top-bottom walls
    if (ball_pos->y <= 0 || ball_pos->y >= HEIGHT) {
        ball_direction->y *= -1;
    }

    // Collision with right-left walls -> Score
    if (ball_pos->x <= 0) {
        resetBall(ball_pos, ball_direction);
        right_score++;
    } else if (ball_pos->x >= WIDTH) {
        resetBall(ball_pos, ball_direction);
        left_score++;
    }

    // Collision with paddles
    Rectangle left_paddle_rec = (Rectangle){paddle1_pos.x, paddle1_pos.y, PADDLE_W, PADDLE_H};
    Rectangle right_paddle_rec = (Rectangle){paddle2_pos.x, paddle2_pos.y, PADDLE_W, PADDLE_H};

    if (CheckCollisionCircleRec(*ball_pos, BALL_RADIUS, left_paddle_rec)) {
        ball_direction->x *= -1;
    } else if (CheckCollisionCircleRec(*ball_pos, BALL_RADIUS, right_paddle_rec)) {
        ball_direction->x *= -1;
    }
}

void displayTexts() {
    char left_text[100];
    itoa(left_score, left_text, 10);
    DrawText(left_text, 20, 20, 50, WHITE);

    char right_text[100];
    itoa(right_score, right_text, 10);
    DrawText(right_text, WIDTH - 50, 20, 50, WHITE);
}


int main() {
    InitWindow(WIDTH, HEIGHT, "Pong Clone");

    srand(time(NULL));

    // Ball
    Vector2 ball_pos = (Vector2){WIDTH / 2, HEIGHT / 2};
    Vector2 ball_direction = (Vector2){direction_choices[rand() % 2], direction_choices[rand() % 2]};

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        handlePaddle(&paddle1_pos, 1);
        handlePaddle(&paddle2_pos, 0);

        handleBall(&ball_pos, &ball_direction);

        displayTexts();

        EndDrawing();
    }
    CloseWindow();
}
