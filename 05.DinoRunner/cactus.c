#include "cactus.h"
#include <stdio.h>


Cactus CreateCactus(float x) {
    Image image = LoadImage("D:\\AltaireTech\\C\\Raylib\\05.DinoRunner\\assets\\cactus.png");
    ImageResize(&image, CACTUS_W, CACTUS_H);
    Texture texture = LoadTextureFromImage(image);
    Vector2 position = (Vector2){.x = x, .y = GROUND_Y - CACTUS_H};
    return (Cactus){.image = image, .texture = texture, .position = position, .active = true};
}

void UpdateCactus(Cactus* cactus, float dt, float speed) {
    cactus->position.x -= speed * dt;

    // If Far left side => Set to be inactive
    if (cactus->position.x < -100) {
        cactus->active = false;
    }
}

void DrawCactus(Cactus* cactus) {
    DrawTextureV(cactus->texture, cactus->position, WHITE);
}
