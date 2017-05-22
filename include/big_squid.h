#ifndef BIG_SQUID_H
#define BIG_SQUID_H

#include "object.h"
#include "sprite.h"

class EvilSquid;

class BigSquid : public Object {
    public:
        BigSquid(EvilSquid *parent);
        void Draw(BITMAP *dest);
        void Update();
        void HandleCollision(int type, void *extra) { }
        void MoveTo(float x, float y);
        void ShootLazer();
    private:
        enum { LEFT, RIGHT } move;
        EvilSquid *parent;
        Sprite stand, openMouth, *sprite;
        Sprite gun1, gun2, *gun;
        float gunLX, gunRX, gunY;
        int shootTimer;
};

#endif

