#include "ink_splat.h"

using namespace std;

InkSplat::InkSplat(float _x, float _y) {
    SetDimensions(10, 10);
    x = _x;
    y = _y;
    for (int i = 0; i < 5; ++ i) {
        inkList.push_back(Ink(rand() % 15, rand() % 15, (rand() % 3) + 3));
    }
}

void InkSplat::Update() {

}

void InkSplat::Draw(BITMAP *dest) {
    int sy = SCREEN_H - (int)(y - camera.GetY());
    set_trans_blender(0, 0, 0, 220);
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
    for (list<Ink>::iterator i = inkList.begin(); i != inkList.end(); ++ i) {
        circlefill(dest, x + i->x, sy + i->y, i->radius, makecol(0, 0, 0));
    }
    solid_mode();
}

void InkSplat::HandleCollision(int type, void *extra) {

}
