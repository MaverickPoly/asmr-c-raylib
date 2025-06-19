#ifndef CACTUS_H
#define CACTUS_H

#include "raylib.h"
#include "config.h"

typedef struct {
    Image image;
    Texture texture;
    Vector2 position;
    bool active;
} Cactus;

Cactus CreateCactus(float x);
void UpdateCactus(Cactus* cactus, float dt, float speed);
void DrawCactus(Cactus* cactus);

#endif
