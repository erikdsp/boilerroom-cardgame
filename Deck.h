#ifndef DECK_H
#define DECK_H
#include <vector>

enum Suits {
    CLUBS,
    DIAMONDS,
    SPADES,
    HEARTS
};


class Card {
     private:
     Suits suit;
     int value;

     public:
     Card(Suits suit_in, int value_in);
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
