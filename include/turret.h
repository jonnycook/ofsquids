#ifndef TURRET_H
#define TURRET_H

#include "monster.h"
#include "sprite.h"

class Turret : public Monster {
    public:
        Turret(float x = 0, float y = 0);
        void Draw(BITMAP *dest);
        void Update();
    private:
        Sprite straight, diagonal;
        Sprite *sprite;
        int tick;
};

#endif
