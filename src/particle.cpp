#include "particle.h"
#include "object.h"
#include "camera.h"

Particle::ParticleList Particle::particleList;

/*
Particle::Particle(void (*_DrawProc)(BITMAP *, int, int, int, int), float _x, float _y, float _vx, float _vy, int _maxLife) :
    DrawProc(_DrawProc), x(_x), y(_y), vx(_vx), vy(_vy), life(_maxLife), maxLife(_maxLife) { }
*/
Particle::Particle(float _x, float _y, float _vx, float _vy, int _radius, int _maxLife, int _color) :
    x(_x), y(_y), vx(_vx), vy(_vy), life(_maxLife), radius(_radius), maxLife(_maxLife), color(_color) { }


/*void Particle::AddParticle(void (*DrawProc)(BITMAP *, int, int, int, int), float x, float y, float vx, float vy, int maxLife) {
    particleList.push_back(Particle(DrawProc, x, y, vx, vy, maxLife));
}*/
void Particle::AddParticle(float x, float y, float vx, float vy, int radius, int maxLife, int color) {
    particleList.push_back(Particle(x, y, vx, vy, radius, maxLife, color));
}


void Particle::UpdateParticles() {
    for (ParticleList::iterator i = particleList.begin(); i != particleList.end(); ++ i) {
        if (i->Update()) {
            i = particleList.erase(i);
        }
    }
}

void Particle::DrawParticles(BITMAP *dest) {
    for (ParticleList::iterator i = particleList.begin(); i != particleList.end(); ++ i) {
        i->Draw(dest);
    }
}

bool Particle::Update() {
    x += vx;
    y += vy;
    if (!(-- life)) {
        return true;
    }
    return false;
}
/*
void Particle::Draw(BITMAP *dest) {
    DrawProc(dest, x, GameToScreen(y), life, maxLife);
}*/

void Particle::Draw(BITMAP *dest) {
    set_trans_blender(0, 0, 0, ((float)life/(float)maxLife) * 255);
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
    circlefill(dest, x, GameToScreen(y), radius, color);
    solid_mode();
}
