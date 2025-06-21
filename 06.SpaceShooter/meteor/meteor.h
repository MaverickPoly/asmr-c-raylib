#ifndef METEOR_H
#define METEOR_H

#include "raylib.h"
#include "../config.h"

typedef struct {
    Image image;
    Texture texture;
    int rotation;
    Rectangle rectangle;
    float speed;
    Vector2 direction;
    bool active;
} Meteor;

Meteor CreateMeteor(int rotation, float x, float y, float speed, Vector2 direction);
void UpdateMeteor(Meteor* meteor, float dt);
void DrawMeteor(Meteor* meteor);

#endif
