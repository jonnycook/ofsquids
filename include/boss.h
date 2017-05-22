#ifndef BOSS_H
#define BOSS_H

#include "monster.h"
#include "sprite.h"

class Boss : public Monster {
    public:
        Boss();
        void Draw(BITMAP *dest);
        void Update();
        void HandleCollision(int type, void *extra);
    private:
        Sprite bigStand, smallLaugh;
        Sprite bigHurt, smallHurt;
};

#endif
