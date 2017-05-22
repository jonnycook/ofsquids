#include "lazer.h"

Lazer::Lazer(float _x, float _y) {
    collisionModel = RECTANGLE;
    SetFlag(F_OBJECT_COLLISION);
    x = _x;
    y = _y;
    w = 1;
    h = 1;
    tick = 0;
}

void Lazer::Update() {
    if (h < 150.0f) {
        h += 5.0f;
    }
    else {
        y -= 5.0f;
    }
    
    if (w < 20.0f) {
        w += 2.0f;
        x -= 1.0f;
    }
}

void Lazer::Draw(BITMAP *dest) {
    int sx = x, sy = GameToScreen(y);
    set_trans_blender(0, 0, 0, 100);
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
    rectfill(dest, sx, sy, sx + w - 1, sy + h - 1, makecol(255, 255, 255));
    solid_mode();
}
