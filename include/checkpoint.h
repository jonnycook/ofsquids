#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "object.h"

class Checkpoint : public Object {
    public:
        Checkpoint();
        void Update() { }
        void Draw(BITMAP *dest);
        void MoveTo(float x, float y);
        void HandleCollision(int type, void *extra);
        static float pos;
};

#endif
