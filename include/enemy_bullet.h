#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include "object.h"

class EnemyBullet : public Object {
    public:
        EnemyBullet(float x, float y, float vx, float vy);
        void Draw(BITMAP *dest);
        void Update();
        void HandleCollision(int type, void *extra = 0);
    private:
        float vx, vy;
        float boost;
};

#endif
