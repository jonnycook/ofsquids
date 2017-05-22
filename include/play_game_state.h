#ifndef PLAY_GAME_STATE_H
#define PLAY_GAME_STATE_H

#include "game_state.h"
#include "camera.h"
#include "object_manager.h"
#include "map.h"

class PlayGameState : public GameState {
    public:
        bool Init();
        void Free();
        GameState *Update();
        void Draw(BITMAP *dest);
    private:
        Map map;
        bool scroll;
};

#endif
