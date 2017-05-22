#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <map>
#include <allegro.h>
#include <string>
#include "sequence.h"
#include "camera.h"

class Sprite {
    struct SpriteInfo {
        std::vector<int> delay;
        std::vector<BITMAP *> image;
    };
    public:
        Sprite(bool loop = true);
        bool Load(char *file);
        void Reset() { sequence.Reset(); }
        bool Update() { return play ? sequence.Update() : false; }
        void Draw(BITMAP *dest, float x, float y, float z);
        void DrawVFlip(BITMAP *dest, float x, float y, float z);
        void DrawHFlip(BITMAP *dest, float x, float y, float z);
        void DrawRotate(BITMAP *dest, float x, float y, float z, int angle);
        void DrawLit(BITMAP *dest, float x, float y, float z, int color);
        void DrawTrans(BITMAP *dest, float x, float y, float z, int alpha);
        void JumpToFrame(int i) { sequence.JumpToFrame(i); }
        void Play() { play = true; }
        void Pause() { play = false; }
        static void FreeSprites();
    private:
        static std::map<char *, SpriteInfo> spriteInfo;
        std::vector<BITMAP *> image;
        Sequence sequence;
        bool play;
        bool loop;
};

#endif
