#include <allegro.h>
#include "game.h"
#include "timer.h"
#include "play_game_state.h"
#include "editor_game_state.h"
#include "data.h"
#include "sprite.h"

Game::Game() {

}

bool Game::Setup() {
    allegro_init();
    install_mouse();
    install_keyboard();
    timer.Install();
    
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    
    buffer = create_bitmap(SCREEN_W, SCREEN_H);
    
    if (!Map::LoadTileImages()) {
        return false;
    }
    
    if (!data.Load()) {
        return false;
    }
    
    gameState = new PlayGameState;
    if (!gameState->Init()) {
        return false;
    }
    
    srand(time(0));

    return true;
}

bool Game::Shutdown() {
    destroy_bitmap(buffer);
    data.Unload();
    gameState->Free();
    Sprite::FreeSprites();
    delete gameState;
}

bool Game::Run() {
    bool done = false;
    unsigned int counter = 0;
    while (!done) {
        while (timer.GetTicks() - counter > 0) {
            if (key[KEY_ESC]) {
                return true;
            }
            if (key[KEY_M]) {
                key[KEY_M] = 0;
                gameState->Free();
                delete gameState;
                gameState = new EditorGameState;
                gameState->Init();
            }
            if (key[KEY_N]) {
                key[KEY_N] = 0;
                gameState->Free();
                delete gameState;
                gameState = new PlayGameState;
                gameState->Init();
            }
            //console.Update();
            if (GameState *gs = gameState->Update()) {
                gameState->Free();
                delete gameState;
                gameState = gs;
                gameState->Init();
            }
            ++ counter;
        }
        
        clear_to_color(buffer, makecol(255, 255, 255));
        //console.Draw(buffer);
        gameState->Draw(buffer);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
    return true;
}

