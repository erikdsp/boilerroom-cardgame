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
    std::vector<Card> m_cards{};
    
    public:
    Deck();
    Deck(std::vector<Card> &deck);
};



#endif
