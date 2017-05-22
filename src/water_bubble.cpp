#include "water_bubble.h"
#include "math.h"
#include "timer.h"
#include "particle.h"
#include "math2.h"

WaterBubble::WaterBubble(Object *_parent) {
    parent = _parent;
    gauge = 100;
}

void WaterBubble::Draw(BITMAP *dest, float vx, float vy) {
    if (gauge >= 0) {
        int tick = (timer.GetTicks() % 45) * 8;
        int radius = 20 + ((float)gauge/100.0f)*25;
        set_trans_blender(0, 0, 0, 100);
        drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
        ellipsefill(dest, parent->GetX() + (parent->GetW() >> 1) - vx, GameToScreen(parent->GetY()) + (parent->GetH() >> 1) + 2 + vy, radius + Cos(tick)*1.0f - abs(vy), radius + Sin(tick)*3.0f - abs(vx), makecol(164, 255, 253));
        solid_mode();
    }
}

void WaterBubble::Update() {

}

bool WaterBubble::Decrease(int i) {
    if (gauge - i < 0) {
        gauge = -1;
        for (int i = 0; i < 50; ++ i) {
            float sin = Sin(i*360.0f/50.0f), cos = Cos(i*360.0f/50.0f);
            Particle::AddParticle(parent->GetX() + (parent->GetW() >> 1), parent->GetY() - (parent->GetH() >> 1), cos*Rand(0.0, 2.0), sin*Rand(0.0f, 2.0), 1, 60, makecol(164, 255, 253));
        }
        return true;
    }
    gauge -= i;
    return false;
}

void WaterBubble::Increase(int i) {
    gauge += i;
}

void WaterBubble::Pop() {
    if (gauge >= 0) {
        gauge = -1;
        for (int i = 0; i < 200; ++ i) {
            float sin = Sin(i*360.0f/200.0f), cos = Cos(i*360.0f/200.0f);
            Particle::AddParticle(parent->GetX() + (parent->GetW() >> 1), parent->GetY() - (parent->GetH() >> 1), cos*Rand(1.0, 2.0), sin*Rand(1.0f, 2.0), 1, 120, makecol(164, 255, 253));
            Particle::AddParticle(parent->GetX() + (parent->GetW() >> 1), parent->GetY() - (parent->GetH() >> 1), cos*Rand(2.0, 3.0), sin*Rand(2.0f, 3.0), 1, 120, makecol(164, 255, 253));
        }
    }
}
