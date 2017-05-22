#include "enemy_bullet.h"
#include "player.h"
#include "water_bullet.h"
#include "math2.h"
#include "particle.h"

using namespace std;

EnemyBullet::EnemyBullet(float _x, float _y, float _vx, float _vy) {
    w = 10;
    h = 10;
    radius = 0;
    SetFlag(F_OBJECT_COLLISION);
    x = _x - 5;
    y = _y + 5;
    vx = _vx;
    vy = _vy;
    boost = 3.0f;
    for (int i = 0; i < 5; ++ i) {
        float cos = Cos(i*360.0f/10.0f), sin = Sin(i*360.0f/10.0f);
        Particle::AddParticle(_x, _y, sin*Rand(1.0f, 3.0f), cos*Rand(1.0f, 3.0f), 1, 20, makecol(244, 253, 138));
    }
}

void EnemyBullet::Update() {
    x += vx * boost;
    y += vy * boost;
    if (radius < 5.0f) {
        radius += 0.3f;
        if (radius >= 5.0f) {
            radius = 5.0f;
        }
    }
    if (boost > 1.0f) {
        boost -= 0.1;
        if (boost < 1.0f) {
            boost = 1.0f;
        }
    }
}

void EnemyBullet::Draw(BITMAP *dest) {
    int sx = (int)x;
    int sy = GameToScreen(y);
    circlefill(dest, sx + (w >> 1), sy + (h >> 1), radius, makecol(255, 255, 255));
}

void EnemyBullet::HandleCollision(int type, void *extra) {
    if (type == OBJECT_COLLISION) {
        if (dynamic_cast<Player *>((Object *)extra) || dynamic_cast<WaterBullet *>((Object *)extra)) {
            SetFlag(F_DEAD);
            for (int i = 0; i < 9; ++ i) {
                float cos = Cos(i*360.0f/9.0f), sin = Sin(i*360.0f/9.0f);
                Particle::AddParticle(x, y, cos*Rand(1.0f, 2.0f), sin*Rand(1.0f, 2.0f), 2, 30, makecol(255, 255, 255));
            }
        }
    }
}
