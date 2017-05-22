#ifndef MONSTER_H
#define MONSTER_H

#include "object.h"

class Monster : public Object {
    public:
        Monster(float x = 0, float y = 0);
        virtual void HandleCollision(int type, void *extra = 0);
};

#endif
