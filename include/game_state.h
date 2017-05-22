#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <allegro.h>

class GameState {
    public:
        virtual bool Init() = 0;
        virtual void Free() = 0;
        virtual GameState *Update() = 0;
        virtual void Draw(BITMAP *dest) = 0;
};

#endif
