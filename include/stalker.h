#ifndef STALKER_H
#define STALKER_H

#include "monster.h"
#include "sprite.h"

class Stalker : public Monster {
    public:
        Stalker(float x = 0, float y = 0);
        void Draw(BITMAP *dest);
        void Update();
        void HandleCollision(int type, void *extra);
    private:
        Sprite stand, walk;
        Sprite *active;
        float vx, vy;
        int state;
};

#endif
