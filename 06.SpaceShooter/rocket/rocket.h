#ifndef ROCKET_H
#define ROCKET_H

#include "raylib.h"
#include "../config.h"

typedef struct {
    Image image;
    Texture texture;
    Rectangle rect;
    Vector2 direction;
} Rocket;

Rocket CreateRocket();
void UpdateRocket(Rocket *rocket, float dt);
void DrawRocket(Rocket *rocket);

#endif
