#include "flyer.h"
#include "math2.h"
#include "object_manager.h"
#include "enemy_bullet.h"

Flyer::Flyer(float _x, float _y) : Monster(_x, _y) {
    SetDimensions(64, 64);
    fly.Load("media/monsters/flyer/fly.anim");
    angle = 0;
    shootTimer = 0;
}

void Flyer::Update() {
    y -= (1/180.0f)*pathY;
    x += ((float)(pathX)/90.0f)*Sin(angle);
    angle += 1;
    if (angle > 360) {
        angle -= 360;
    }
    fly.Update();
    
    if (++ shootTimer > 120) {
        shootTimer = 0;
        objManager.AddObject(new EnemyBullet(x + (w >> 1), y - h, 0.0f, -2.0f));
    }
}

void Flyer::Draw(BITMAP *dest) {
    fly.Draw(dest, x, y, z);
}
