#include "Deck.h"
#include <iostream>


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
    // output: print welcome info and game rules
    print_blackjack_welcome();

    // while (1)
    bool game_open{true};
    while(game_open)
    {
        // -- BIDDING --
        // enter bids, loop through players and ask for bid
        for (auto player : players)
        {
            player.enter_bid(next_id);      // pass by reference, if successful will update next_id
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
            players_to_play = false;        // dummy - remove when functions are implemented
        }

        // -- DEALER DRAWS CARDS --
        
        // print both dealer cards, dealer_hide_card = false
        deck.print_cards(CardHolder::DEALER, false);    

        int dealer_min{};    
        int dealer_max{ deck.max_value(CardHolder::DEALER) };
        // bool dealer_has_natural { deck.has_natural(CardHolder::DEALER) };
        bool dealer_playing{ dealer_max < 17 };
        while (dealer_playing)
        {
            deck.draw_card(CardHolder::DEALER);
            deck.print_cards(CardHolder::DEALER, false); 
            dealer_min = deck.min_value(CardHolder::DEALER);     // evaluate first ACE as 1
            dealer_max = deck.max_value(CardHolder::DEALER);     // evaluate first ACE as 11
            if ( ( dealer_max >= 17 ) )
            {
                dealer_playing = false;
            }
            dealer_playing = false;     // dummy - remove when functions are implemented
        }

        // -- CALCULATE WINNER --
            for (auto player : players)
            {
                // calculates and prints outcome
                BlackjackOutcome player_result = deck.calculate_win(player.get_id());  
                // updates player's purse
                player.score_round(player_result);
            }

        // -- CLEAR THE TABLE --
        deck.clear_the_table(gen.m_mt_rand);

        // -- PLAY ANOTHER ROUND --
        // output: prompt
        // input: y or n
        game_open = false;  // dummy - remove when functions are implemented
    }
    



    return 0;
}

// output: print welcome info and game rules
void print_blackjack_welcome()
{
    std::cout << "                                                                            \n"   
              << "'||''|.   '||                  '||            '||'                 '||      \n"    
              << " ||   ||   ||   ....     ....   ||  ..         ||   ....     ....   ||  ..  \n"
              << " ||'''|.   ||  '' .||  .|   ''  || .'          ||  '' .||  .|   ''  || .'   \n"
              << " ||    ||  ||  .|' ||  ||       ||'|.          ||  .|' ||  ||       ||'|.   \n"
              << ".||...|'  .||. '|..'|'  '|...' .||. ||.    || .|'  '|..'|'  '|...' .||. ||. \n"
              << "                                            '''                             \n"
              << "                         A GAME BY SUVX24 GBG                               \n\n";
 
}