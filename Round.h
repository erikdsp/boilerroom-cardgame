#ifndef BLACKJACK_ROUND
#define BLACKJACK_ROUND
#include "Deck.h"
#include "Player.h"
#include <vector>
#include <stack>

class Round
{
    private:
    bool m_keepPlaying;
    std::stack<Card> m_shuffled_deck;
    std::vector<BlackjackSeat> m_seats;
    BlackjackDealer m_dealer;
    
    public:
    Round(int num_of_decks);
    void place_bids();
    void deal_the_game();               // tilldela kort till players och dealer.
    void players_play();                // all the players. Fundera ut hela kedjan. Flera under-medlemsfunktioner?
    bool dealer_play_another_card();    // evaluate the dealer hand
    void dealer_play();                 // add a card to dealer hand
    void calculate_score();             // evaluate all hands
    void play_round();                  // eventuellt för att sätta ihop alla medlemsfunktioner ovan
};



#endif