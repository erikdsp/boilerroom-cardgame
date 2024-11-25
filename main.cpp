#include "Game.h"
#include <iostream>
#include <vector>

int main()
{
    Game blackjack;
    Player player("Jennifer", 200.0);

    while(1){
        blackjack.join_game(&player);

        blackjack.run();
    }

    return 0;
}