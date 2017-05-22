#include "editor_game_state.h"

bool EditorGameState::Init() {
    map.Create(SCREEN_W >> 5, 225);
    mapEditor.SetMap(&map);
    return true;
}

void EditorGameState::Free() {

}

GameState *EditorGameState::Update() {
    mapEditor.Update();
    return 0;
}

void EditorGameState::Draw(BITMAP *dest) {
    mapEditor.Draw(dest);
}

