#ifndef PARTICLE_H
#define PARTICLE_H

#include <allegro.h>
#include <list>

class Particle {
    public:
        typedef std::list<Particle> ParticleList;
        static void AddParticle(float x, float y, float vx, float vy, int radius, int maxLife, int color);
        //static void AddParticle(void (*DrawProc)(BITMAP *, int, int, int, int), float x, float y, float vx, float vy, int maxLife);
        static void DrawParticles(BITMAP *dest);
        static void UpdateParticles();
    private:
        static ParticleList particleList;
        Particle(float x = 0, float y = 0, float vx = 0, float vy = 0, int radius = 0, int maxLife = 0, int color = 0);
//        Particle(void (*DrawProc)(BITMAP *, int, int, int, int) = 0, float x = 0, float y = 0, float vx = 0, float vy = 0, int maxLife = 0);
        void Draw(BITMAP *dest);
        bool Update();
        void (*DrawProc)(BITMAP *, int, int, int, int);
        float x, y;
        float vx, vy;
        int life;
        int maxLife;
        int radius;
        int color;
};

#endif
