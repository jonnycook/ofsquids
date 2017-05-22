#ifndef COMET_H
#define COMET_H

#include "object.h"
#include "sprite.h"

class Comet : public Object {
    public:
        Comet();
        void Draw(BITMAP *dest);
        void Update();
        void HandleCollision(int type, void *extra);
        void MoveTo(float x, float y);
    private:
        Sprite sprite;
        float vz;
        bool falling;
};

#endif
