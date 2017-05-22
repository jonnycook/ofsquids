#ifndef OBJECT_H
#define OBJECT_H

//#include <allegro.h>
#include "camera.h"

#define GameToScreen(Y) SCREEN_H - (int)(Y - camera.GetY())

class Map;

class Object {
    public:
        enum {
            OBJECT_COLLISION,
            TILE_COLLISION
        };
        enum {
            F_DEAD = 1,
            F_Z_AXIS = 4,
            F_TILE_COLLISION = 8,
            F_OBJECT_COLLISION = 16
        };
        
        Object();
        virtual ~Object() { }
        virtual void Draw(BITMAP *dest) = 0;
        void DrawInfo(BITMAP *dest);
        virtual void Update() = 0;
        virtual void HandleCollision(int type, void *extra = 0) = 0;
        void SetFlag(int flag) { flags |= flag; }
        void ClearFlag(int flag) { flags &= ~flag; }
        bool TestFlag(int flag) const { return flags & flag; }
        virtual void MoveTo(float _x, float _y) { x = _x; y = _y; }
        float GetX() const { return x; }
        float GetY() const { return y; }
        void SetX(float _x) { x = _x; }
        void SetY(float _y) { y = _y; }
        int GetW() const { return w; }
        int GetH() const { return h; }
        int GetTriggerRange() const { return triggerRange; }
        int SetTriggerRange(int i) { triggerRange = i; }
        void BackupCoords() { lastX = x; lastY = y; lastZ = z; }
        void CheckTileCollision(Map &map);
        static bool Collides(Object *obj1, Object *obj2) {
            if (obj1->collisionModel == RECTANGLE || obj2->collisionModel == RECTANGLE) {
                float x1 = obj1->GetX(), y1 = obj1->GetY(), w1 = obj1->GetW(), h1 = obj1->GetH();
                float x2 = obj2->GetX(), y2 = obj2->GetY(), w2 = obj2->GetW(), h2 = obj2->GetH();
                if (x1 + w1 < x2) return false;
                if (x1 > x2 + w2) return false;
                if (y1 < y2 - h2) return false;
                if (y1 - h1 > y2) return false;
                return true;
            }
            float v1 = (obj1->x + (obj1->GetW() >> 1)) - (obj2->x + (obj2->GetW() >> 1));
            float v2 = (obj1->y - (obj1->GetH() >> 1)) - (obj2->y - (obj2->GetH() >> 1));
            float v3 = obj1->radius + obj2->radius;
            return v1*v1 + v2*v2 < v3*v3;
        }
    protected:
        void RestoreCoords() { x = lastX; y = lastY; z = lastZ; }
        void SetDimensions(int w, int h);
        float x, y, z;
        int w, h;
        float radius;
        int flags;
        int triggerRange;
        enum { CIRCLE, RECTANGLE } collisionModel;

    private:
        float lastX, lastY, lastZ;
};

#endif
