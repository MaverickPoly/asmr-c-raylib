#include "laser.h"


Laser CreateLaser(float x, float y) {
    Image image = LoadImage("..\\06.SpaceShooter\\images\\laser.png");
    Texture texture = LoadTextureFromImage(image);
    Rectangle rect = (Rectangle) {x, y, LASER_W, LASER_H};
    return (Laser) {
        .image = image,
        .texture = texture,
        .rect = rect,
        .active = true
    };
}

void UpdateLaser(Laser* laser, float dt) {
    laser->rect.y -= LASER_SPEED * dt;

    if (laser->rect.y + LASER_H <= 0) {
        laser->active = false;
    }
}

void DrawLaser(Laser* laser) {
    DrawTexture(laser->texture, (int) laser->rect.x, (int) laser->rect.y, WHITE);
}
