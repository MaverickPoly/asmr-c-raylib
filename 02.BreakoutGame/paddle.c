#include "paddle.h"

#include "config.h"


Paddle CreatePaddle(const float x, const float y) {
    return (Paddle) {.rect = {x, y, PADDLE_W, PADDLE_H}, .direction = {0, 0}};
}

void UpdatePaddle(Paddle* paddle, const float dt) {
    if (IsKeyDown(KEY_LEFT)) paddle->direction.x = -1;
    else if (IsKeyDown(KEY_RIGHT)) paddle->direction.x = 1;
    else paddle->direction.x = 0;

    paddle->rect.x += paddle->direction.x * dt * PADDLE_SPEED;

    if (paddle->rect.x <= 0) paddle->rect.x = 0;
    if (paddle->rect.x + PADDLE_W >= WIDTH) paddle->rect.x = WIDTH - PADDLE_W;
}

void DrawPaddle(const Paddle* paddle) {
    DrawRectangleRec(paddle->rect, LIGHTGRAY);
}
