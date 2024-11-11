#ifndef DECK_H
#define DECK_H
#include <vector>

enum Suits {
    HEARTS,
    CLUBS,
    DIAMONDS,
    SPADES
};
// enum Pips {
//     TWO=2,

// }

class Card {
     private:
     int suit;
     int value;

     public:
     int get_val(int card_value);
     
};
class Deck {
    private:
    std::vector<Card> cards;
    
    public:
    Deck(std::vector<Card> &deck);
};

// Card(Suit, value);


#endif