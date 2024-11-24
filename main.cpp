#include "Deck.h"
#include <iostream>

namespace BlackjackRules
{
    const int minimum_bid {10};     // currency is SEK
}

void print_blackjack_welcome();

int main()
{

    // Same as RandomGenerator but in main:
    // std::random_device rd;
    // std::seed_seq ss { rd(), rd(), rd(), rd() };
    // std::mt19937 mt_rand{ ss };

    RandomGenerator gen{};
    BlackjackDeck deck{ 6 , gen.m_mt_rand };
    std::vector<Player> players { {"Player 1" , 1}, {"Player 2" , 2} };
    int next_id { 1 };

    /**
     * TODO: Implement Card Dealer in main 
     */

    // -- WELCOME --
    print_blackjack_welcome();

    bool game_open{true};
    while(game_open)
    {
        // -- BIDDING --
        // enter bids, loop through players and ask for bid
        for (auto player : players)
        {
            player.enter_bid(next_id);      // pass by reference, if successful will update next_id
            // std::cout << player.is_playing();
        }
        // -- DEALING CARDS --
        for (int i = 0 ; i < 2 ; ++i)
        {
                for (auto player : players)
            {
                deck.draw_card(player.get_id());  
                deck.print_cards(player.get_id());
            }
            deck.draw_card(CardHolder::DEALER);
            deck.print_cards(CardHolder::DEALER);
        }
        // output for each card?? wait 500 ms for each card?

        // if a player has a natural. DOES DEALER SHOW HAND TO ALL PLAYERS?
        // -- HIT OR STAND --
        bool players_to_play {true};
        while (players_to_play)
        {    
            int count = 0; 
            for (auto player : players)
            {
                if (player.is_playing()) 
                {
                    bool hit = player.hit_or_stand();
                    if (hit)
                    {
                        count++;
                        deck.print_cards(player.get_id());
                    }
                }
            }
            if (count == 0) players_to_play = false;
        }

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
        game_open = false;
    }
    



    /**   
     * DONE: New data structure for Deck 
     * TODO: Functions that loops through card vector
     * PROS: more robust data integrity = less room for bugs
     * CONS: requires more vector looping = slower
    */




    return 0;
}

// output: print welcome info and game rules
void print_blackjack_welcome()
{
    std::cout << "Welcome to Black Jack\n";    
}