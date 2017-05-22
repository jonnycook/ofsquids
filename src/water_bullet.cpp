#include "water_bullet.h"
#include "timer.h"
#include "math.h"
#include "player.h"
#include "particle.h"
#include "puddle.h"
#include "math2.h"

using namespace std;

void WaterParticle(BITMAP *dest, int x, int y, int life, int maxLife) {
    set_trans_blender(0, 0, 0, ((float)life/(float)maxLife) * 255);
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
    circlefill(dest, x, y, 1, makecol(164, 255, 253));
    solid_mode();
}

WaterBullet::WaterBullet(float _x, float _y) {
    SetFlag(F_TILE_COLLISION | F_OBJECT_COLLISION);
    ClearFlag(F_Z_AXIS);
    SetDimensions(22, 20);
    maxRadius = radius;
    radius = 0;
    x = _x - (w >> 1);
    y = _y + (h >> 1);
    for (int i = 0; i < 100; ++ i) {
        float angle = i*180.0/100.0f;
        float sin = Sin(angle), cos = Cos(angle);
        Particle::AddParticle(_x, _y, cos*Rand(0.0, 3.0), sin*Rand(0.0f, 3.0), 1, 50, makecol(164, 255, 253));
    }
    die = false;
}

void WaterBullet::Update() {
    y += 8.0f;
    if (radius < maxRadius) {
        radius += 0.9f;
        if (radius >= maxRadius) {
            radius = maxRadius;
        }
    }
}

void WaterBullet::Draw(BITMAP *dest) {
    int sy = SCREEN_H - (int)(y - camera.GetY());
    int tick = (timer.GetTicks() % 45) * 8;
    set_trans_blender(0, 0, 0, 100);
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
    ellipsefill(dest, x + (w >> 1), sy + (h >> 1), radius + 1.0f*Cos(tick), radius + 2.0f + 1.0f*Sin(tick), makecol(164, 255, 253));
    solid_mode();
}

void WaterBullet::HandleCollision(int type, void *extra) {
    if (type == TILE_COLLISION) {
        SetFlag(F_DEAD);
    }
    else if (!dynamic_cast<Player *>((Object *)extra) && !dynamic_cast<Puddle *>((Object *)extra)) {
        SetFlag(F_DEAD);
    }
    if (TestFlag(F_DEAD)) {
        for (int i = 0; i < 30; ++ i) {
            float angle = i*180.0/30.0f;
            float sin = Sin(angle), cos = Cos(angle);
            Particle::AddParticle(x + (w >> 1), y, cos*Rand(0.0, 3.0), -sin*Rand(0.0f, 3.0), 1, 20, makecol(164, 255, 253));
        }
    }
}
