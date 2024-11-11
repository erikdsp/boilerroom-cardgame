#ifndef DECK_H
#define DECK_H
#include <vector>
#include <random>   // for std::mt19937, std::random_device, std::seed_seq and std::uniform_int_distribution
#include <iostream>

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

class DeckShuffle {
    private:
    public:
    void print_number(std::mt19937 rnd)
    {
        std::cout << std::uniform_int_distribution { 1, 52 }(rnd);
    }
    int generate_number(std::mt19937 rnd, int min, int max)
    {
            return std::uniform_int_distribution { min, max }(rnd);
    }

};


#endif
