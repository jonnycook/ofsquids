#include "checkpoint.h"
#include "player.h"

float Checkpoint::pos = 32;

Checkpoint::Checkpoint() {
    h = 5;
    w = SCREEN_W;
    collisionModel = RECTANGLE;
    SetFlag(F_OBJECT_COLLISION);
}

void Checkpoint::MoveTo(float _x, float _y) {
    x = 0;
    y = _y;
}

void Checkpoint::Draw(BITMAP *dest) {
    //hline(dest, 0, GameToScreen(y), SCREEN_W - 1, 0);
}

void Checkpoint::HandleCollision(int type, void *extra) {
    if (type == OBJECT_COLLISION) {
        if (dynamic_cast<Player *>((Object *)extra)) {
            pos = y;
        }
    }
}
