#include "comet.h"
#include "player.h"
#include "math2.h"
#include "particle.h"

using namespace std;

void DustParticle(BITMAP *dest, int x, int y, int life, int maxLife) {
    set_trans_blender(0, 0, 0, ((float)life/(float)maxLife) * 255);
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
    circlefill(dest, x, y, 10, makecol(255, 255, 102));
    solid_mode();
}

void DirtParticle(BITMAP *dest, int x, int y, int life, int maxLife) {
    set_trans_blender(0, 0, 0, ((float)life/(float)maxLife) * 255);
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
    circlefill(dest, x, y, 1, makecol(0, 0, 0));
    solid_mode();
}

void SmokeParticle(BITMAP *dest, int x, int y, int life, int maxLife) {
    set_trans_blender(0, 0, 0, ((float)life/(float)maxLife) * 255);
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
    circlefill(dest, x, y, 10, makecol(255, 255, 255));
    solid_mode();
}

Comet::Comet() {
    w = 128;
    h = 128;
    radius = 64;
    sprite.Load("media/monsters/comet/comet.anim");
    z = 150.0f;
    vz = 0.1f;
}

void Comet::MoveTo(float _x, float _y) {
    x = _x - (w >> 1);
    y = _y + (h >> 1);
}

void Comet::Update() {
    if (z > 0.0f) {
        z -= vz;
        vz *= 1.1f;
        if (z < 0.0f) {
            SetFlag(F_OBJECT_COLLISION);
            sprite.JumpToFrame(1);
            z = 0;
            for (int i = 0; i < 40; ++ i) {
                float cos = Cos((360.0f/40.0f) * (float)i);
                float sin = Sin((360.0f/40.0f) * (float)i);
                Particle::AddParticle(x + radius + cos*radius, y - radius + radius*sin, cos*Rand(0.0f, 2.5f), sin*Rand(0.0f, 2.5f), 10, 40, makecol(255, 255, 102));
            }
            for (int i = 0; i < 100; ++ i) {
                float cos = Cos((360.0f/100.0f) * (float)i);
                float sin = Sin((360.0f/100.0f) * (float)i);
                Particle::AddParticle(x + radius + cos*radius, y - radius + radius*sin, cos*Rand(0.0f, 5.0f), sin*Rand(0.0f, 5.0f), 1, 40, makecol(0, 0, 0));
            }
            for (int i = 0; i < 100; ++ i) {
                float cos = Cos((360.0f/100.0f) * (float)i);
                float sin = Sin((360.0f/100.0f) * (float)i);
                Particle::AddParticle(x + radius + cos*radius, y - radius + radius*sin, cos*10.0f, sin*10.0f, 10, 120, makecol(255, 255, 255));
            }
        }
    }
}

void Comet::Draw(BITMAP *dest) {
    if (z > 80.0f) {
        int sy = GameToScreen(y);
        set_trans_blender(0, 0, 0, 100);
        drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
        circlefill(dest, x + 64, sy + 64, 128.0f * ((50.0f - (z - 100.0f))/50.0f), 0);
        solid_mode();
    }
    if (z < 100.0f) {
        sprite.Draw(dest, x - 10, y + 10, z);
    }
}

void Comet::HandleCollision(int type, void *extra) {

}
