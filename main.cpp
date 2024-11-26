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
    std::vector<Player> players { {"Player 1"}, {"Player 2"} };
    Player dealer { "House", CardHolder::DEALER };
    int next_id { 1 };

    // std::cout << Cards::value_out.at(1) << "\n";

    /**
     * TODO: Implement Card Dealer in main 
     */

    // -- WELCOME --
    // output: print welcome info and game rules
    print_blackjack_welcome();

    bool game_open{true};
    while(game_open)
    {
        // -- BIDDING --
        // enter bids, loop through players and ask for bid
        for (auto& player : players )
        {
            player.enter_bid(next_id);      // pass by reference, if successful will update next_id
        }

        // -- DEALING CARDS --
        for (int i = 0 ; i < 2 ; ++i)
        {
            for (auto& player : players)
            {
                if (player.is_playing())
                {
                    deck.draw_card(player.get_id());  
                    if (i != 0)
                    {
                        deck.print_cards(player);
                    }
                }
            }
            deck.draw_card(CardHolder::DEALER);
            if (i != 0)
            {
                deck.print_cards(dealer);
            }
        }


        // check for natural
        // if a player has a natural, dealer does not show card. But evaluate against player

        // -- HIT OR STAND --
        bool players_to_play {true};
        while (players_to_play)
        {    
            int count = 0; 
            for (auto& player : players)
            {
                // check if player is bust
                if (deck.is_bust(player.get_id())) 
                {
                    player.set_playing(false);
                }
                // ask active players for hit or stand
                if (player.is_playing()) 
                {
                    BlackjackRules::HitOrStand decision = player.hit_or_stand();
                    // std::cout << "Hit: " << decision << "\n";
                    if (decision == BlackjackRules::HIT)
                    {
                        deck.draw_card(player.get_id());
                        count++;
                        deck.print_cards(player);
                    }
                    else if (decision == BlackjackRules::STAND)
                    {
                        player.set_playing(false);
                    }
                    else 
                    {
                        std::cerr << "Error: hit_or_stand returned ERROR\n";
                    }
                }
            }
            if (count == 0) players_to_play = false;
        }

        // -- DEALER DRAWS CARDS --
        
        // print both dealer cards, dealer_hide_card = false
        deck.print_cards(dealer, false);    

        int dealer_min{};    
        int dealer_max{ deck.max_value(CardHolder::DEALER) };
        bool dealer_playing{ dealer_max < 17 };
        while (dealer_playing)
        {
            deck.draw_card(CardHolder::DEALER);
            deck.print_cards(dealer, false); 
            dealer_min = deck.min_value(CardHolder::DEALER);     // evaluate first ACE as 1
            dealer_max = deck.max_value(CardHolder::DEALER);     // evaluate first ACE as 11
            if ( ( dealer_max >= 17 && dealer_max <= 21 ) || dealer_min >= 17 )
            {
                dealer_playing = false;
            }
        }

        // -- CALCULATE WINNER --
            for ( auto& player : players )
            {
                if (player.get_id() > 0)    // players in the game has id > 0
                {
                    // calculates outcome
                    BlackjackOutcome player_result = deck.calculate_win(player);  
                
                    // prints outcome and updates player's purse
                    player.score_round(player_result);
                }
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