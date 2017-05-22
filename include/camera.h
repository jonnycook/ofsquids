#ifndef CAMERA_H
#define CAMERA_H

#include <allegro.h>

#define camera Camera::GetInstance()

class Camera {
    public:
        float GetY() const { return y; }
        void SetRange(float _minY, float _maxY) { minY = _minY; maxY = _maxY; }
        void Scroll(float amnt) { y = MID(minY, y + amnt, maxY); }
        void Jump(float to) { y = MID(minY, to, maxY); }
        static Camera &GetInstance();
        bool ReachedEnd() const { return ABS(maxY - y) < 1.0f; }
    private:
        Camera();
        float y;
        float minY, maxY;
};

#endif
