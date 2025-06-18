#ifndef BRICK_H
#define BRICK_H

#include "raylib.h"

typedef struct {
    Rectangle rect;
    Color color;
    int active;
} Brick;

Brick CreateBrick(const double x, const double y, const Color color);
void DrawBrick(const Brick* brick);


#endif
