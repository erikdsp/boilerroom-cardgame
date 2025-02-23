#include "Deck.h"
#include <iostream>
using Players = std::vector<Player>;

void print_blackjack_welcome();
const int find_next_id(const Players& p);
bool play_again();

int main()
{
    BlackjackDeck deck{ 6 };
    std::vector<Player> players { {"Player 1"}, {"Player 2"} };
    Player dealer { "House", CardHolder::DEALER };

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
            player.enter_bid(find_next_id(players));      // pass by reference, if successful will update next_id
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

        // -- CHECK FOR NATURAL -- 
        // if a player has a natural, dealer does not show card. But evaluate against player
        for (auto& player : players)
        {
            if (deck.has_natural(player.get_id()))
            {
                // calculates outcome
                BlackjackOutcome player_result = deck.calculate_win(player);                  
                // prints outcome, updates player's purse and resets player id
                player.score_round(player_result);
            }
        }

        // -- HIT OR STAND --
        bool players_to_play {true};
        int last_active_player{};       // used to avoid excessive printing
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
                    // print player's hand if it's not the last thing printed
                    if (player.get_id() != last_active_player) deck.print_cards(player);
                    // the heart of the game
                    BlackjackRules::HitOrStand decision = player.hit_or_stand();
                    last_active_player = player.get_id();
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
        deck.clear_the_table();

        // -- PLAY ANOTHER ROUND --
        game_open = play_again();

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

const int find_next_id(const Players& p)
{
    int id{0};
    for (auto& player : p)
    {
        if (player.get_id() >= id) id = player.get_id() + 1;
    }
    return id;
}

bool play_again()
{
    std::string input{};
    std::cout << "q)Quit, p)Play another round -> ";

    while(std::cin >> input)
    {
        switch (input.at(0))
        {
            case 'q':
                return false;   
            case 'p':
                return true;
            default:
            std::cout << "Invalid option. q)Quit, p)Play another round -> ";
        }
    }
    return true;
}