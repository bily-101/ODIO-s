#include "Game.h"

int main() {

    Game game("ODIO",
              640, 484,
              4, 5,
              false);

    while (!game.getWindowShouldClose()) {

        game.update();
        game.render();
    }

    return 0;
}