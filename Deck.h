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
     Suits m_suit;
     int m_value;

     public:
     Card(Suits suit, int value);

     int get_value();    
};

class Deck {
    private:
    std::vector<Card> cards;
    
    public:
    Deck(std::vector<Card> &deck);
};

// Card(Suit, value);


#endif
