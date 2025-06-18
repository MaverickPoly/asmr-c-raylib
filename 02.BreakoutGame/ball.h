#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "paddle.h"

typedef struct {
    Vector2 position;
    Vector2 direction;
    Vector2 speed;
} Ball;

Ball CreateBall(const Vector2 direction);
int UpdateBall(Ball* ball, float dt, Paddle* paddle);
void DrawBall(const Ball* ball);


#endif
