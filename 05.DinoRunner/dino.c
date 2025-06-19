#include "dino.h"


Dino CreateDino() {
    Image image = LoadImage("D:\\AltaireTech\\C\\Raylib\\05.DinoRunner\\assets\\dino.png");
    ImageResize(&image, DINO_W, DINO_H);
    const Texture texture = LoadTextureFromImage(image);
    const Vector2 position = (Vector2){200, 400};
    return (Dino){
        .image = image,
        .texture = texture,
        .velocity_y = 0,
        .on_ground = false,
        .position = position
    };
}

void UpdateDino(Dino* dino, float dt) {
    if (IsKeyPressed(KEY_SPACE) && dino->on_ground) {
        dino->velocity_y = -JUMP_FORCE;
        dino->on_ground = false;
    }

    dino->velocity_y += GRAVITY * dt;
    dino->position.y += dino->velocity_y * dt;

    // On floor
    if (dino->position.y + DINO_H >= GROUND_Y) {
        dino->position.y = GROUND_Y - DINO_H;
        dino->velocity_y = 0;
        dino->on_ground = true;
    }
}

void DrawDino(Dino* dino) {
    DrawTexture(dino->texture, dino->position.x, dino->position.y, WHITE);
}