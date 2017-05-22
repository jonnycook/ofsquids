#include "end_game_state.h"
#include "global.h"
bool EndGameState::Init() {

}

void EndGameState::Free() {

}

GameState *EndGameState::Update() {
    if (key[KEY_ENTER]) {
        done = true;
    }
    return 0;
}

void EndGameState::Draw(BITMAP *dest) {
    clear_to_color(dest, makecol(0, 0, 0));
    textout_centre_ex(dest, font, "Knock knock...", SCREEN_W/2, 10, makecol(255, 255, 255), -1);
    textout_centre_ex(dest, font, "Who's there?", SCREEN_W/2, 20, makecol(255, 255, 255), -1);
    textout_centre_ex(dest, font, "Orange.", SCREEN_W/2, 30, makecol(255, 255, 255), -1);
    textout_centre_ex(dest, font, "Orange who?", SCREEN_W/2, 40, makecol(255, 255, 255), -1);
    textout_centre_ex(dest, font, "Orange you glad I didn't say... BANANA?", SCREEN_W/2, 50, makecol(255, 255, 255), -1);
}
