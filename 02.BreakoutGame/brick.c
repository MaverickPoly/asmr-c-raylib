#include "brick.h"
#include "config.h"

Brick CreateBrick(const double x, const double y, const Color color) {
    return (Brick) {.rect = {x, y, BRICK_W - PADDING, BRICK_H - PADDING}, .color = color, .active = 1};
}

void DrawBrick(const Brick* brick) {
    DrawRectangleRec(brick->rect, brick->color);
}