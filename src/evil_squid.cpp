#include "evil_squid.h"
#include "big_squid.h"
#include "object_manager.h"
#include "water_bullet.h"
#include "particle.h"
#include "math2.h"
#include "global.h"

EvilSquid::EvilSquid() {
    SetDimensions(36, 36);
    SetFlag(F_OBJECT_COLLISION);
    laugh.Load("media/monsters/boss/evillaugh.anim");
    ouch.Load("media/monsters/boss/evilouch.anim");
    sprite = &laugh;
    bigSquid = new BigSquid(this);
    objManager.AddObject(bigSquid);
    health = 15;
    hack = 0;
}

void EvilSquid::Update() {
    if (sprite->Update()) {
        if (sprite == &ouch) {
            sprite = &laugh;
        }
    }
}

void EvilSquid::Draw(BITMAP *dest) {
    sprite->Draw(dest, x - 10, y + 6, z);
}

void EvilSquid::HandleCollision(int type, void *extra) {
    if (type == OBJECT_COLLISION) {
        if (dynamic_cast<WaterBullet *>((Object *)extra)) {
            if (++ hack == 2) {
                sprite = &ouch;
                bigSquid->ShootLazer();
                if (!(-- health)) {
                    SetFlag(F_DEAD);
                    bigSquid->SetFlag(F_DEAD);
                    beatTheGame = true;
                    for (int i = 0; i < 40; ++ i) {
                        float cos = Cos((360.0f/40.0f) * (float)i);
                        float sin = Sin((360.0f/40.0f) * (float)i);
                        Particle::AddParticle(x + radius + cos*radius, y - radius + radius*sin, cos, sin, 10, 80, makecol(255, 130, 130));
                        Particle::AddParticle(x + radius + cos*radius, y - radius + radius*sin, cos*2.0f, sin*2.0f, 10, 70, makecol(255, 155, 155));
                        Particle::AddParticle(x + radius + cos*radius, y - radius + radius*sin, cos*2.5f, sin*2.5f, 10, 60, makecol(255, 170, 170));
                        Particle::AddParticle(x + radius + cos*radius, y - radius + radius*sin, cos*3.0f, sin*3.0f, 10, 50, makecol(255, 195, 195));
                        Particle::AddParticle(x + radius + cos*radius, y - radius + radius*sin, cos*3.5f, sin*3.5f, 10, 40, makecol(255, 220, 220));
                    }
                }
                hack = 0;
            }
        }
    }
}

void EvilSquid::MoveTo(float _x, float _y) {
    Object::MoveTo(_x, _y);
    bigSquid->MoveTo(_x + (w >> 1), _y - (h >> 1) - 10);
}

