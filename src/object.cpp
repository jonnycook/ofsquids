#include "object.h"
#include "map.h"
#include <cmath>

using namespace std;

Object::Object() {
    collisionModel = CIRCLE;
    x = 0;
    y = 0;
    z = 0;
    w = 0;
    h = 0;
    radius = 0;
    flags = 0;
    triggerRange = SCREEN_H + (SCREEN_H >> 1);
    SetFlag(F_Z_AXIS);
}

void Object::DrawInfo(BITMAP *dest) {
    int sx = (int)x;
    int sy = SCREEN_H - (int)(y - camera.GetY());
    circle(dest, sx + (w >> 1), sy + (h >> 1), radius, 0);
    rect(dest, sx, sy, sx + w, sy + h, 0);
    putpixel(dest, sx, sy, makecol(255, 0, 0));
}

void Object::SetDimensions(int _w, int _h) {
    w = _w;
    h = _h;
    radius = sqrt((float)(w*w + h*h)) / 3.0f;
}

void Object::CheckTileCollision(Map &map) {
    int intX = (int)x, intY = (int)y;
    int beginX = intX >> 5, beginY = intY >> 5;
    int endX = (intX + w) >> 5, endY = (intY - h) >> 5;
    for (int i = beginY; i >= endY; -- i) {
        for (int j = beginX; j <= endX; ++ j) {
            if (map.GetTile(j, i).solid) {
                HandleCollision(TILE_COLLISION, (void *)map.GetTile(j, i).index);
            }
        }
    }
}
