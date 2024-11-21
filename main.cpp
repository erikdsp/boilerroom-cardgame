#include "Deck.h"
#include <iostream>


int main()
{

// Don't need to be a class. But maybe can be for now
RandomGenerator gen{};
BlackjackDeck deck{ 6 , gen.m_mt_rand };
// deck.add_standard_deck();
deck.print_cards();

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

