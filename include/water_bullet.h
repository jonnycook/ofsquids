#ifndef WATER_BULLET_H
#define WATER_BULLET_H

#include "object.h"

class WaterBullet : public Object {
    public:
        WaterBullet(float x, float y);
        void Update();
        void Draw(BITMAP *dest);
        void HandleCollision(int type, void *extra);
    private:
        float maxRadius;
        bool die;
};

#endif
