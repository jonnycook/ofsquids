#ifndef GAME_H
#define GAME_H

#include "game_state.h"

class Game {
    public:
        Game();
        bool Setup();
        bool Shutdown();
        bool Run();
    private:
        BITMAP *buffer;
        GameState *gameState;
};

#endif
