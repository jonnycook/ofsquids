#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "sprite.h"
#include "water_bubble.h"

class Player : public Object {
    public:
        Player(float x = 0, float y = 0);
        void Draw(BITMAP *dest);
        void Update();
        void HandleCollision(int type, void *extra);
        void SetPlayer(int i);
        void MoveTo(float x, float y);
        static Player *one, *two;
        bool dead;
    private:
        enum {
            K_UP,
            K_DOWN,
            K_LEFT,
            K_RIGHT,
            K_FIRE,
            K_DASH,
            K_DROP
        };
        int control[7];
        Sprite sprite;
        BITMAP *head;
        int gunTimer;
        int dashTimer;
        int dehydrateTimer;
        WaterBubble waterBubble;
        float headX, headY;
        float headDX, headDY;
        float headForce;
        bool headSeek;
        float vx, vy;
};

#endif

