#ifndef CUBE_H
#define CUBE_H

#include "raylib.h"
#include "config.h"

typedef struct {
    Rectangle rectangle;
    double velocity_y;
} Cube;

Cube CreateCube();
void UpdateFlappyCube(Cube* cube);
void DrawFlappyCube(Cube* cube);

#endif //CUBE_H
