#include <cmath>
#include "player.h"
#include "object_manager.h"
#include "water_bullet.h"
#include "ink_splat.h"
#include "puddle.h"
#include "data.h"
#include "math2.h"
#include "timer.h"
#include "checkpoint.h"
#include "tiles.h"

using namespace std;

Player *Player::one = 0, *Player::two = 0;

Player::Player(float _x, float _y) : waterBubble(this) {
    SetDimensions(36, 36);
    SetFlag(F_OBJECT_COLLISION | F_TILE_COLLISION);
    x = _x;
    y = _y;
    dead = false;
    dashTimer = 0;
    gunTimer = 0;
    headX = 0;
    headY = 0;
    headDX = 0;
    headDY = 0;
    headForce = 1.0f;
    headSeek = false;
    vx = 0;
    vy = 0;
    dehydrateTimer = 0;
}

void Player::MoveTo(float _x, float _y) {
    x = _x;
    y = Checkpoint::pos;
}

void Player::SetPlayer(int i) {
    if (i == 1) {
        sprite.Load("media/squid1.anim");
        head = (BITMAP *)data[SQUID1TOP];
        control[K_UP] = KEY_W;
        control[K_DOWN] = KEY_S;
        control[K_LEFT] = KEY_A;
        control[K_RIGHT] = KEY_D;
        control[K_FIRE] = KEY_SPACE;
        control[K_DASH] = KEY_LSHIFT;
        control[K_DROP] = KEY_X;
    }
    else if (i == 2) {
        sprite.Load("media/squid2.anim");
        head = (BITMAP *)data[SQUID2TOP];
        control[K_UP] = KEY_8_PAD;
        control[K_DOWN] = KEY_5_PAD;
        control[K_LEFT] = KEY_4_PAD;
        control[K_RIGHT] = KEY_6_PAD;
        control[K_FIRE] = KEY_ENTER;
        control[K_DASH] = KEY_RSHIFT;
        control[K_DROP] = KEY_0_PAD;
    }
}

void Player::Update() {
    if (!dead) {
        if (!headSeek) {
            headDX = 0;
            headDY = 0;
        }
        if (key[KEY_O]) {
            key[KEY_O] = 0;
            if (TestFlag(F_TILE_COLLISION | F_OBJECT_COLLISION)) {
                ClearFlag(F_TILE_COLLISION | F_OBJECT_COLLISION);
            }
            else {
                SetFlag(F_TILE_COLLISION | F_OBJECT_COLLISION);
            }
        }
        if (key[control[K_DASH]]) {
            if (!dashTimer) {
                headForce = 3.0f;
                dashTimer = 60;
                waterBubble.Decrease(10);
                if (key[control[K_UP]]) {
                    vy += 10.0f;
                    headDY = 10.0f;
                }
                if (key[control[K_DOWN]]) {
                    vy -= 10.0f;
                    headDY = -10.0f;
                }
                if (key[control[K_LEFT]]) {
                    vx -= 10.0f;
                    headDX = 10.0f;
                }
                if (key[control[K_RIGHT]]) {
                    vx += 10.0f;
                    headDX = -10.0f;
                }
            }
            else {
                -- dashTimer;
            }
        }
        else {
            dashTimer = 0;
        }
        
        
        if (!dashTimer) {
            if (key[control[K_UP]]) {
                vy += 0.5f;
                if (!headSeek) {
                    headDY = -10.0f;
                }
            }
            if (key[control[K_DOWN]]) {
                vy -= 0.5f;
                if (!headSeek) {
                    headDY = 10.0f;
                }
            }
            if (key[control[K_LEFT]]) {
                vx -= 0.5f;
                if (!headSeek) {
                    headDX = -10.0f;
                }
            }
            if (key[control[K_RIGHT]]) {
                vx += 0.5f;
                if (!headSeek) {
                    headDX = 10.0f;
                }
            }
        }

        x += vx;
        y += vy;
        vx *= 0.9f;
        vy *= 0.9f;

        x = MID(0, x, SCREEN_W - w - 1);
        y = MID(camera.GetY() + h, y, camera.GetY() + SCREEN_H);

        if (!gunTimer) {
            if (key[control[K_FIRE]]) {
                gunTimer = 20;
                objManager.AddObject(new WaterBullet(x + (w >> 1), y));
                dead = waterBubble.Decrease(5);
                headDY += 10.0f;
                headForce = 2.0f;
            }
        }
        else {
            -- gunTimer;
        }
        
        if (key[control[K_DROP]]) {
            key[control[K_DROP]] = 0;
            objManager.AddObject(new InkSplat(x + (w >> 1), y - (h >> 1)), false);
        }
        
        if (camera.ReachedEnd()) {
            waterBubble.Set(100);
        }
        else {
            if (++ dehydrateTimer >= 20) {
                dehydrateTimer = 0;
                if (waterBubble.Decrease(1)) {
                    dead = true;
                }
            }
        }
        waterBubble.Update();
    }
    else {
        if (!headSeek) {
            headDX = Cos(timer.GetTicks() % 360) * 10.0f;
            headDY = Sin(timer.GetTicks() % 360) * 10.0f;
            headForce = 1.0f;
        }
    }
    float dist = DistSq(headX, headY, headDX, headDY);
    if (dist > 1.0f) {
        float angle = Atan2(headDY - headY, headDX - headX);
        float speed = sqrt(dist)/10.0f;
        headX += Cos(angle)*speed*headForce;
        headY += Sin(angle)*speed*headForce;
        headSeek = true;
    }
    else {
        headForce = 1.0f;
        headSeek = false;
    }
    sprite.Update();
}

void Player::Draw(BITMAP *dest) {
    int sy = GameToScreen(y), sx = x;
    sprite.Draw(dest, x - 10, y + 6, z);
    set_clip_rect(dest, sx, sy, sx + w, SCREEN_H);
    draw_sprite(dest, head, sx + headX - 10, sy + headY - 6);
    set_clip_rect(dest, 0, 0, dest->w - 1, dest->h - 1);
    waterBubble.Draw(dest, vx, vy);
}

void Player::HandleCollision(int type, void *extra) {
    if (type == TILE_COLLISION) {
        waterBubble.Pop();
        dead = true;
    }
    else {
        if (dynamic_cast<Puddle *>((Object *)extra)) {
            waterBubble.Increase(10);
        }
        else if (!dynamic_cast<WaterBullet *>((Object *)extra) && !dynamic_cast<Player *>((Object *)extra) && !dynamic_cast<Checkpoint *>((Object *)extra)) {
            waterBubble.Pop();
            dead = true;
        }
    }
}
