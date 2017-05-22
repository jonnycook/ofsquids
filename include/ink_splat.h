#ifndef INK_SPLAT_OBJECT_H
#define INK_SPLAT_OBJECT_H

#include "object.h"
#include <list>

class InkSplat : public Object {
    struct Ink {
        Ink(int _x, int _y, int _radius) : x(_x), y(_y), radius(_radius) { }
        int x, y;
        int radius;
    };
    public:
        InkSplat(float _x, float _y);
        void Draw(BITMAP *dest);
        void Update();
        void HandleCollision(int type, void *extra);
    private:
        std::list<Ink> inkList;
};

#endif
