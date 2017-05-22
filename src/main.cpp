#include <allegro.h>
#include "game.h"

int main() {
    Game game;
    if (game.Setup()) {
        game.Run();
    }
    game.Shutdown();
    return 0;
}
END_OF_MAIN()
