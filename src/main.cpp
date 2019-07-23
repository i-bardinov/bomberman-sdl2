#include <string>

#include "Game.h"

int main()
{
    // init game
    bomberman::Game game(std::string("bomberman"), 800, 600);
    // run game loop
    game.run();

    return 0;
}
