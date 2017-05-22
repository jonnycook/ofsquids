#include "puddle.h"
#include "timer.h"
#include "math2.h"
#include "player.h"
#include "particle.h"

Puddle::Puddle() {
    SetFlag(F_OBJECT_COLLISION);
    SetDimensions(32, 32);
}

void Puddle::Update() {

}

void Puddle::Draw(BITMAP *dest) {
    int tick = ((timer.GetTicks() % 45) * 8) + (rand() % 20);
    set_trans_blender(0, 0, 0, 100);
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
    ellipsefill(dest, x + (w >> 1), GameToScreen(y) + (h >> 1) + 2, radius + Cos(tick)*1.0f, radius + Sin(tick)*1.0f, makecol(164, 255, 253));
    solid_mode();
}

void Puddle::HandleCollision(int type, void *extra) {
    Player *player = dynamic_cast<Player *>((Object *)extra);
    if (player) {
        SetFlag(F_DEAD);
        for (int i = 0; i < 50; ++ i) {
            float sin = Sin(i*360.0f/50.0f), cos = Cos(i*360.0f/50.0f);
            Particle::AddParticle(x + (w >> 1), y - (h >> 1), cos*Rand(0.0, 2.0), sin*Rand(0.0f, 2.0), 1, 60, makecol(164, 255, 253));
        }
    }
}
