#include "cube.h"

Cube CreateCube() {
    return (Cube){
        .rectangle = (Rectangle){ WIDTH / 2 - CUBE_WIDTH / 2, HEIGHT / 2 - CUBE_HEIGHT / 2, CUBE_WIDTH, CUBE_HEIGHT},
        .velocity_y = 0.0
    };
};

void UpdateFlappyCube(Cube* cube) {
    float dt = GetFrameTime();

    // Jump
    if (IsKeyPressed(KEY_SPACE)) {
        cube->velocity_y = -JUMP_FORCE;
    }
    if (IsKeyDown(KEY_LEFT)) {
        cube->rectangle.x -= SPEED * dt;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        cube->rectangle.x += SPEED * dt;
    }

    // Apply Gravity
    cube->velocity_y += GRAVITY;
    cube->rectangle.y += cube->velocity_y * dt;

    // Keep on screen
    if (cube->rectangle.y + CUBE_HEIGHT > HEIGHT) {
        cube->rectangle.y = HEIGHT - CUBE_HEIGHT;
        cube->velocity_y = 0;
    }
};

void DrawFlappyCube(Cube* cube) {
    DrawRectangleRec(cube->rectangle, YELLOW);
};
