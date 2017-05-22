#ifndef PACER_H
#define PACER_H

#include "monster.h"
#include "sprite.h"

class Pacer : public Monster {
    public:
        Pacer(float x = 0, float y = 0);
        void Draw(BITMAP *dest);
        void Update();
        void SetPath(int x1, int y1, int x2, int y2);
    private:
        Sprite walk;
        enum { UP, DOWN, LEFT, RIGHT } dir;
        struct {
            float x1, y1;
            float x2, y2;
        } path;
};

#endif
