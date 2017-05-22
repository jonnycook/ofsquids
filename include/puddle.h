#ifndef PUDDLE_H
#define PUDDLE_H

#include "object.h"

class Puddle : public Object {
    public:
        Puddle();
        void Draw(BITMAP *dest);
        void Update();
        void HandleCollision(int type, void *extra);
};

#endif
