#include "Deck.h"
#include <iostream>


int main()
{

// Don't need to be a class. But maybe can be for now
RandomGenerator gen{};
BlackjackDeck deck{ 6 , gen.m_mt_rand };
// deck.add_standard_deck();
// deck.print_cards();

std::vector<Player> players {{"Player 1" , 1}, {"Player 2" , 2}};

std::cout << std::boolalpha;
for (auto& player : players)
{
    std::cout << player.get_name() << ", ID: " << player.get_id() 
    << ", Is playing: " << player.is_playing() << "\n";
}




/**
 * TODO: Implement Card Dealer in main 
 */

/**   
 * DONE: New data structure for Deck 
 * TODO: Functions that loops through card vector
 * PROS: more robust data integrity = less room for bugs
 * CONS: requires more vector looping = slower
*/




return 0;
}

