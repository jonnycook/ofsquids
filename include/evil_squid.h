#ifndef EVIL_SQUID_H
#define EVIL_SQUID_H

#include "object.h"
#include "sprite.h"

class BigSquid;

class EvilSquid : public Object {
    public:
        EvilSquid();
        void Update();
        void Draw(BITMAP *dest);
        void HandleCollision(int type, void *extra);
        void MoveTo(float x, float y);
        int GetHealth() const { return health; }
    private:
        Sprite laugh, ouch, *sprite;
        BigSquid *bigSquid;
        int health;
        int hack;
};

#endif
