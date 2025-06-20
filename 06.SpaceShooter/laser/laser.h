#ifndef LASER_H
#define LASER_H

#include "raylib.h"
#include "../config.h"

typedef struct {
    Image image;
    Texture texture;
    Rectangle rect;
    bool active;
} Laser;

Laser CreateLaser(float x, float y);
void UpdateLaser(Laser* laser, float dt);
void DrawLaser(Laser* laser);

#endif