#ifndef END_GAME_STATE_H
#define END_GAME_STATE_H

#include "game_state.h"

class EndGameState : public GameState {
    public:
        bool Init();
        void Free();
        GameState *Update();
        void Draw(BITMAP *dest);
};

#endif
