#ifndef WATER_BUBBLE_H
#define WATER_BUBBLE_H

#include "object.h"

class WaterBubble {
    public:
        WaterBubble(Object *parent);
        void Draw(BITMAP *dest, float vx, float vy);
        void Update();
        bool Decrease(int i);
        void Increase(int i);
        void Set(int i) { if (i == 0) Pop(); else gauge = i; }
        void Pop();
    private:
        Object *parent;
        int gauge;
};

#endif
