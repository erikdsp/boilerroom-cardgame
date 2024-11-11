#ifndef DECK_H
#define DECK_H
#include <vector>

enum Suits {
    CLUBS,
    DIAMONDS,
    SPADES,
    HEARTS
};

enum Values {
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};


class Card {
     private:
     Suits m_suit;
     Values m_value;

     public:
     Card(Suits suit, Values value);

     Values get_value();
     Suits getsuit();    
};

class Deck {
    private:
    std::vector<Card> m_cards{};
    
    public:
    Deck();
    Deck(std::vector<Card> &deck);
};



#endif
