#include "monster.h"
#include "water_bullet.h"
#include "particle.h"
#include "math2.h"

Monster::Monster(float _x, float _y) {
    SetFlag(F_OBJECT_COLLISION | F_TILE_COLLISION);
    x = _x;
    y = _y;
}

void Monster::HandleCollision(int type, void *extra) {
    if (type == OBJECT_COLLISION) {
        WaterBullet *obj = dynamic_cast<WaterBullet *>((Object *)extra);
        if (obj) {
            SetFlag(F_DEAD);
            static const int deathColors[] = {
                makecol(238, 225, 120),
                makecol(238, 233, 213),
                makecol(200, 130, 83),
                makecol(255, 224, 164),
                makecol(255, 255, 255)
            };
            for (int i = 0; i < 20; ++ i) {
                float cos = Cos(i*360.0f/20.0f), sin = Sin(i*360.0f/20.0f);
                Particle::AddParticle(x + (w >> 1), y - (h >> 1), cos*Rand(0.0f, 5.0f), sin*Rand(0.0f, 5.0f), 2, 30, deathColors[rand() % (sizeof(deathColors)/sizeof(int))]);
            }
        }
    }
}
