#include <stdlib.h>
#include "Game.hpp"

int main() {
    srand(time(0));
    Game game;
    game.run();
    return EXIT_SUCCESS;
}