#ifndef PADDLE_H
#define PADDLE_H

#include "raylib.h"

typedef struct {
    Rectangle rect;
    Vector2 direction;
} Paddle;

Paddle CreatePaddle(const float x, const float y);
void UpdatePaddle(Paddle* paddle, const float dt);
void DrawPaddle(const Paddle* paddle);


#endif
