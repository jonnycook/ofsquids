#ifndef LAZER_H
#define LAZER_H

#include "object.h"

class Lazer : public Object {
    public:
        Lazer(float x, float y);
        void Draw(BITMAP *dest);
        void Update();
        void HandleCollision(int type, void *extra) { }
    private:
        int tick;
};

#endif
