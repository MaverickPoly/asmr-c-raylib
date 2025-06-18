#include "ball.h"

#include <math.h>

#include "config.h"


Ball CreateBall(const Vector2 direction) {
    return  (Ball){.position = {WIDTH / 2, HEIGHT / 2}, .direction = direction, .speed = {BALL_SPEED, BALL_SPEED}};
};

int UpdateBall(Ball* ball, const float dt, Paddle* paddle) {
    // Moving
    ball->position.x += ball->direction.x * dt * ball->speed.x;
    ball->position.y += ball->direction.y * dt * ball->speed.y;

    // Keep ball on scree
    if (ball->position.y - BALL_RADIUS <= 0) ball->direction.y *= -1;
    if (ball->position.x - BALL_RADIUS <= 0 || ball->position.x + BALL_RADIUS >= WIDTH) ball->direction.x *= -1;
    if (CheckCollisionCircleRec(ball->position, BALL_RADIUS, paddle->rect)) {
        double relative_x = (ball->position.x - (paddle->rect.x + PADDLE_W / 2)) / (PADDLE_W / 2);
        double speed_magnitude = sqrt(pow(ball->speed.x, 2) + pow(ball->speed.y, 2));
        ball->speed.x = relative_x * speed_magnitude;
        ball->direction.y *= -1;
    }

    if (ball->position.y + BALL_RADIUS >= HEIGHT) return 1;
    return 0;
};

void DrawBall(const Ball* ball) {
    DrawCircleV(ball->position, BALL_RADIUS, RED);
};

