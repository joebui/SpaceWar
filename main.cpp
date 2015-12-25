#include <stdlib.h>
#include "Game.hpp"

int main() {
    srand(time(0));
    Game game;
    game.run();

//    float random = ((float) rand()) / (float) (RAND_MAX / 6);
//    cout<< random << " ";
    return EXIT_SUCCESS;
}