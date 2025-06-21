#include "rocket.h"

#include "raymath.h"

Rocket CreateRocket() {
    Image image = LoadImage("..\\06.SpaceShooter\\images\\player.png");
    Texture texture = LoadTextureFromImage(image);
    Rectangle rect = (Rectangle) {
        WIDTH / 2 - ROCKET_W / 2,
        HEIGHT - ROCKET_H - 40,
        ROCKET_W, ROCKET_H
    };
    Vector2 direction = (Vector2) {0,  0};
    Rocket rocket = (Rocket) {
        .image = image, .texture = texture,
        .rect = rect, .direction = direction
    };
    return rocket;
}

void UpdateRocket(Rocket* rocket, float dt) {
    rocket->direction.x = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
    rocket->direction.y = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);
    rocket->direction = Vector2Normalize(rocket->direction);

    rocket->rect.x += rocket->direction.x * dt * ROCKET_SPEED;
    rocket->rect.y += rocket->direction.y * dt * ROCKET_SPEED;

    if (rocket->rect.x < 0) rocket->rect.x = 0;
    if (rocket->rect.x >= WIDTH - ROCKET_W) rocket->rect.x = WIDTH - ROCKET_W;
    if (rocket->rect.y < 0) rocket->rect.y = 0;
    if (rocket->rect.y >= HEIGHT - ROCKET_H) rocket->rect.y = HEIGHT - ROCKET_H;
}

void DrawRocket(Rocket *rocket) {
    DrawTexture(rocket->texture, rocket->rect.x, rocket->rect.y, WHITE);
}
