#include "play_game_state.h"
#include "player.h"
#include "stalker.h"
#include "object.h"
#include "sprite.h"
#include "particle.h"
#include "object_manager.h"
#include "global.h"
#include "end_game_state.h"
#include "checkpoint.h"

bool PlayGameState::Init() {
    if (!map.Load("map001.map")) {
        return false;
    }
    if (!objManager.LoadObjects("map001.obj")) {
        return false;
    }

    camera.SetRange(0, (map.GetH() << 5) - SCREEN_H);
    camera.Jump(Checkpoint::pos);
    scroll = true;
    return true;
}

void PlayGameState::Free() {
    objManager.Free();
}

GameState *PlayGameState::Update() {
    map.Update();
    objManager.Update(map);
    Particle::UpdateParticles();
    if (scroll) {
        camera.Scroll(2.0f);
    }
    if (key[KEY_B]) {
        scroll = !scroll;
        key[KEY_B] = 0;
    }
    if (key[KEY_UP]) {
        camera.Scroll(2.0f);
    }
    else if (key[KEY_DOWN]) {
        camera.Scroll(-2.0f);
    }
    if (beatTheGame) {
        return new EndGameState;
    }
    
    if (Player::one->dead && Player::two->dead) {
        objManager.Free();
        objManager.LoadObjects("map001.obj");
        camera.Jump(Checkpoint::pos);
    }
        
    return 0;
}

void PlayGameState::Draw(BITMAP *dest) {
    map.Draw(dest);
    objManager.Draw(dest);
    Particle::DrawParticles(dest);
}
