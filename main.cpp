#include "Deck.h"
#include <iostream>

namespace BlackjackRules
{
    const int minimum_bid {10};     // currency is SEK
}


int main()
{

    // std::random_device rd;
    // std::seed_seq ss { rd() };
    // std::mt19937 mt_rand{ ss };

// Don't need to be a class. But maybe can be for now
RandomGenerator gen{};
BlackjackDeck deck{ 6 , gen.m_mt_rand };
// deck.add_standard_deck();
// deck.print_cards();

std::vector<Player> players {{"Player 1" , 1}, {"Player 2" , 2}};

// std::cout << std::boolalpha;
// for (auto& player : players)
// {
//     std::cout << player.get_name() << ", ID: " << player.get_id() 
//     << ", Is playing: " << player.is_playing() << "\n";
// }

/**
 * TODO: Implement Card Dealer in main 
 */

// -- WELCOME --
// output: print welcome info and game rules

// while (1)
// -- BIDDING --
// enter bids, loop through players and ask for bid
//          if (purse > bid) {current_bid = bid, purse -= bid}
// output: prompt
// input: bid
// -- DEALING CARDS --
// loop 2 times - draw_card for each player, then dealer
// display function for dealer, only shows 1 card
// output: print cards
// -- HIT OR STAND --
// loop until all players is_playing() return false
// ask each player in turn hit_or_stand
// output: prompt
// input: h or s
// output: print new cards
// -- DEALER DRAWS CARDS --
// loop until conditions for dealer play are satisfied
// output: show both dealer's cards
//     Rule: if total >= 17 stand (counting ace as 11)
// if max_value >= 17 && max_value <= 21 stand  - check ACE as 11 
// else if min_value >= 17                      - check ACE as 1
// output: show new cards (until done)
// -- CALCULATE WINNER --
// loop players - if player is bust, bid lost       (current_bid = 0)
// if dealer is bust - standing players adds bid    (purse += current_bid * 2, current_bid = 0)
// if player > dealer players get bid               (purse += current_bid * 2, current_bid = 0)
// if player < dealer nothing                       (current_bid = 0)
// if player == dealer, bid is returned             (purse += current_bid, current_bid = 0)
// loop through players, adjust current_bid, purse
// output: outcome of game
// -- CLEAR THE TABLE --
// clear_the_table(), sets all used cards to CardHolder::DISCARD
// clear_the_table also checks if remaining CardHolder::DECK < 50 (assuming 6 cards in deck)
// and then reshuffles deck 
// -- PLAY ANOTHER ROUND --
// output: prompt
// input: y or n


/**   
 * DONE: New data structure for Deck 
 * TODO: Functions that loops through card vector
 * PROS: more robust data integrity = less room for bugs
 * CONS: requires more vector looping = slower
*/




return 0;
}

