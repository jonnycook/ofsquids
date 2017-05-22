#include "big_squid.h"
#include "evil_squid.h"
#include "object_manager.h"
#include "enemy_bullet.h"
#include "lazer.h"

using namespace std;

BigSquid::BigSquid(EvilSquid *_parent) {
    parent = _parent;
    SetDimensions(158, 155);
    stand.Load("media/monsters/boss/bigstand.anim");
    openMouth.Load("media/monsters/boss/bigouch.anim");
    gun1.Load("media/monsters/boss/biggun1.anim");
    gun2.Load("media/monsters/boss/biggun2.anim");
    sprite = &stand;
    gun = &gun1;
    move = LEFT;
    shootTimer = 0;
}

void BigSquid::Update() {
    if (sprite->Update()) {
        if (sprite == &openMouth) {
            sprite = &stand;
        }
    }
    if (shootTimer >= (parent->GetHealth() < 10 ? 1 : 5)) {
        if (gun->Update()) {
            shootTimer = 0;
            if (gun == &gun1) {
                gun = &gun2;
                objManager.AddObject(new EnemyBullet(x + gunLX + 3, gunY - 93, -1.0f, -1.0f));
                objManager.AddObject(new EnemyBullet(x + gunLX + 52, gunY - 93, 1.0f, -1.0f));
                objManager.AddObject(new EnemyBullet(x + gunRX + 3, gunY - 93, -1.0f, -1.0f));
                objManager.AddObject(new EnemyBullet(x + gunRX + 52, gunY - 93, 1.0f, -1.0f));
            }
            else if (gun == &gun2) {
                gun = &gun1;
                objManager.AddObject(new EnemyBullet(x + gunLX + 28, gunY - 98, 0.0f, -1.0f));
                objManager.AddObject(new EnemyBullet(x + gunRX + 28, gunY - 98, 0.0f, -1.0f));
            }
        }
    }
    else {
        ++ shootTimer;
    }
    if (parent->GetHealth() < 5) {
        if (move == LEFT) {
            x -= 1.0f;
            parent->SetX(parent->GetX() - 1.0f);
            if (x < 100.0f) {
                move = RIGHT;
            }
        }
        else if (move == RIGHT) {
            x += 1.0f;
            parent->SetX(parent->GetX() + 1.0f);
            if (x > SCREEN_W - 100.0f - w) {
                move = LEFT;
            }
        }
    }
}

void BigSquid::Draw(BITMAP *dest) {
    sprite->Draw(dest, x, y, z);
    gun->Draw(dest, x + gunLX, gunY, z);
    gun->DrawHFlip(dest, x + gunRX, gunY, z);
}

void BigSquid::MoveTo(float _x, float _y) {
    x = _x - (w >> 1);
    y = _y + (h >> 1);
    gunLX = (w >> 1) - 110;
    gunRX = (w >> 1) + 110 - 58;
    gunY = y - 20;
}

void BigSquid::ShootLazer() {
    sprite = &openMouth;
    objManager.AddObject(new Lazer(x + 75, y - 135));
}
