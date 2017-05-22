#include "stalker.h"
#include "player.h"
#include <cmath>

using namespace std;

Stalker::Stalker(float _x, float _y) : Monster(_x, _y) {
    SetDimensions(76, 76);
    SetFlag(F_TILE_COLLISION | F_OBJECT_COLLISION);
    stand.Load("media/monsters/stalker/stand.anim");
    walk.Load("media/monsters/stalker/walk.anim");
    active = &walk;
}

void Stalker::Update() {
    float dx = Player::one->GetX() - x;
    float dy = Player::one->GetY() - y;
    const float speed = 2.5f;
    if (abs(dy) < abs(dx)) {
        if (dx > 0.0f) {
            x += speed;
        }
        else if (dx < 0.0f) {
            x -= speed;
        }
    }
    else {
        if (dy > 0.0f) {
            y += speed;
        }
        else if (dy < 0.0f) {
            y -= speed;
        }
    }
    active->Update();
}

void Stalker::Draw(BITMAP *dest) {
    active->Draw(dest, x, y, z);
}

void Stalker::HandleCollision(int type, void *extra) {
    Monster::HandleCollision(type, extra);
    if (type == TILE_COLLISION) {
        RestoreCoords();
    }
    else if (dynamic_cast<Stalker *>((Object *)extra)) {
        RestoreCoords();
    }
}

