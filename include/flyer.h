#ifndef FLYER_H
#define FLYER_H

#include "monster.h"
#include "sprite.h"

class Flyer : public Monster {
    public:
        Flyer(float x = 0, float y = 0);
        void Draw(BITMAP *dest);
        void Update();
        void SetPath(int x, int y) { pathX = x; pathY = y; }
    private:
        int pathX, pathY;
        Sprite fly;
        float angle;
        int shootTimer;
};

#endif
