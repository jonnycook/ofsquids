#include "sprite.h"

std::map<char *, Sprite::SpriteInfo> Sprite::spriteInfo;

Sprite::Sprite(bool _loop) : sequence(_loop) {
    play = true;
}

void Sprite::Draw(BITMAP *dest, float x, float y, float z) {
    int sy = SCREEN_H - (int)(y - camera.GetY());
    int sx = (int)x;
    if (!image.empty()) {
        BITMAP *bmp = image[sequence.GetFrame()];
        float multiplier = 1.0f + z/10.0f;
        int nw = bmp->w * multiplier, nh = bmp->h * multiplier;
        stretch_sprite(dest, bmp, sx - (nw >> 1) + (bmp->w >> 1), sy - (nh >> 1) + (bmp->h >> 1), nw, nh);
    }
    else {
        rect(dest, sx, sy, sx + 31, sy + 31, makecol(255, 0, 255));
    }
}

void Sprite::DrawVFlip(BITMAP *dest, float x, float y, float z) {
    int sy = SCREEN_H - (int)(y - camera.GetY());
    int sx = (int)x;
    if (!image.empty()) {
        draw_sprite_v_flip(dest, image[sequence.GetFrame()], sx, sy);
    }
    else {
        rect(dest, sx, sy, sx + 31, sy + 31, makecol(255, 0, 255));
    }
}

void Sprite::DrawHFlip(BITMAP *dest, float x, float y, float z) {
    int sy = SCREEN_H - (int)(y - camera.GetY());
    int sx = (int)x;
    if (!image.empty()) {
        draw_sprite_h_flip(dest, image[sequence.GetFrame()], sx, sy);
    }
    else {
        rect(dest, sx, sy, sx + 31, sy + 31, makecol(255, 0, 255));
    }
}

void Sprite::DrawRotate(BITMAP *dest, float x, float y, float z, int angle) {
    int sy = SCREEN_H - (int)(y - camera.GetY());
    int sx = (int)x;
    if (!image.empty()) {
        rotate_sprite(dest, image[sequence.GetFrame()], sx, sy, itofix(angle));
    }
    else {
        rect(dest, sx, sy, sx + 31, sy + 31, makecol(255, 0, 255));
    }
}

bool Sprite::Load(char *file) {
    if (!spriteInfo.count(file)) {
        PACKFILE *pf = pack_fopen(file, "r");
        SpriteInfo *info = &spriteInfo[file];

        if (!pf) {
            return false;
        }

        char tag[7];
        tag[6] = 0;

        pack_fread((void *)tag, 6, pf);
        if (strcmp("<anim>", tag)) {
            return false;
        }

        int size = pack_igetl(pf);

        for (int i = 0; i < size; ++ i) {
            BITMAP *bmp = load_bmp_pf(pf, NULL);
            int delay = pack_igetl(pf);
            int ox = pack_igetl(pf);
            int oy = pack_igetl(pf);
            info->image.push_back(bmp);
            info->delay.push_back(delay);
        }
        pack_fclose(pf);
    }
    SpriteInfo *info = &spriteInfo[file];
    for (int i = 0; i < info->delay.size(); ++ i) {
        sequence.AddFrame(info->delay[i]);
    }
    image = info->image;
    return true;
}

void Sprite::FreeSprites() {
    for (std::map<char *, SpriteInfo>::iterator i = spriteInfo.begin(); i != spriteInfo.end(); ++ i) {
        for (std::vector<BITMAP *>::iterator j = i->second.image.begin(); j != i->second.image.end(); ++ j) {
            destroy_bitmap(*j);
        }
    }
}
