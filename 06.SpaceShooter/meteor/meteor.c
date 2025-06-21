#include "meteor.h"

Meteor CreateMeteor(int rotation, float x, float y, float speed, Vector2 direction) {
    Image image = LoadImage("..\\06.SpaceShooter\\images\\meteor.png");
    ImageRotate(&image, rotation);
    Texture texture = LoadTextureFromImage(image);
    Rectangle rect = (Rectangle){x, y, METEOR_W, METEOR_H};
    Meteor m = (Meteor){
        .image = image,
        .texture = texture,
        .rotation = rotation,
        .rectangle = rect,
        .speed = speed,
        .direction = direction,
        .active = true,
    };
    return m;
}

void UpdateMeteor(Meteor* meteor, float dt) {
    meteor->rectangle.x += meteor->speed * meteor->direction.x * dt;
    meteor->rectangle.y += meteor->speed * meteor->direction.y * dt;

    if (meteor->rectangle.y >= HEIGHT) {
        meteor->active = false;
    }
}

void DrawMeteor(Meteor* meteor) {
    DrawTexture(
        meteor->texture,
        meteor->rectangle.x,
        meteor->rectangle.y,
        WHITE
    );
}
