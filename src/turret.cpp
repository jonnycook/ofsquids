#include "turret.h"
#include "enemy_bullet.h"
#include "object_manager.h"
#include "particle.h"
#include "math.h"

Turret::Turret(float _x, float _y) : Monster(_x, _y), diagonal(false), straight(false) {
    SetDimensions(32, 32);
    diagonal.Load("media/monsters/turret/diagonal.anim");
    straight.Load("media/monsters/turret/straight.anim");
    sprite = &diagonal;
    tick = 0;
}

void Turret::Update() {
    if (tick == 30) {
        if (sprite->Update()) {
            tick = 0;
            sprite->Reset();
            if (sprite == &diagonal) {
                objManager.AddObject(new EnemyBullet(x, y, -1.0f, 1.0f));
                objManager.AddObject(new EnemyBullet(x + 31, y, 1.0f, 1.0f));
                objManager.AddObject(new EnemyBullet(x, y - 31, -1.0f, -1.0f));
                objManager.AddObject(new EnemyBullet(x + 31, y - 31, 1.0f, -1.0f));
                sprite = &straight;
            }
            else {
                objManager.AddObject(new EnemyBullet(x + 16, y, 0.0f, 1.0));
                objManager.AddObject(new EnemyBullet(x, y - 16, -1.0f, 0.0f));
                objManager.AddObject(new EnemyBullet(x + 31, y - 16, 1.0f, 0.0f));
                objManager.AddObject(new EnemyBullet(x + 16, y - 31, 0.0f, -1.0f));
                sprite = &diagonal;
            }
        }
    }
    else {
        ++ tick;
    }
}

void Turret::Draw(BITMAP *dest) {
    sprite->Draw(dest, x, y, z);
}

