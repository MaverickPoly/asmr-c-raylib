#ifndef DINO_H
#define DINO_H

#include "raylib.h"
#include "config.h"

typedef struct {
    Image image;
    Texture texture;
    double velocity_y;
    bool on_ground;
    Vector2 position;
} Dino;

Dino CreateDino();
void UpdateDino(Dino* dino, float dt);
void DrawDino(Dino* dino);

#endif //DINO_H
