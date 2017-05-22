#ifndef EDITOR_GAME_STATE_H
#define EDITOR_GAME_STATE_H

#include "game_state.h"
#include "map_editor.h"

class EditorGameState : public GameState {
    public:
        bool Init();
        void Free();
        GameState *Update();
        void Draw(BITMAP *dest);
    private:
        MapEditor mapEditor;
        Map map;
};

#endif
