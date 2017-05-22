#include "pacer.h"

Pacer::Pacer(float _x, float _y) : Monster(_x, _y) {
    SetDimensions(48, 48);
    walk.Load("media/monsters/pacer/walkh.anim");
}

void Pacer::SetPath(int x1, int y1, int x2, int y2) {
    path.x1 = x1;
    path.y1 = y1;
    path.x2 = x2;
    path.y2 = y2;
    if (x1 == x2) {
        dir = DOWN;
    }
    else {
        dir = RIGHT;
    }
}


void Pacer::Update() {
    switch (dir) {
        case UP:
            y += 1.0f;
            if (y > path.y2) {
                dir = DOWN;
                y = path.y2;
            }
            break;
        case DOWN:
            y -= 1.0f;
            if (y < path.y1) {
                dir = UP;
                y = path.y1;
            }
            break;
        case LEFT:
            x -= 1.0f;
            if (x < path.x1) {
                dir = RIGHT;
                x = path.x1;
            }
            break;
        case RIGHT:
            x += 1.0f;
            if (x > path.x2) {
                dir = LEFT;
                x = path.x2;
            }
    }
    walk.Update();
}


void Pacer::Draw(BITMAP *dest) {
    switch (dir) {
        case UP:
            walk.DrawRotate(dest, x, y, z, 64);
            break;
        case DOWN:
            walk.DrawRotate(dest, x, y, z, -64);
            break;
        case LEFT:
            walk.Draw(dest, x, y, z);
            break;
        case RIGHT:
            walk.DrawHFlip(dest, x, y, z);
            break;
    }
}
