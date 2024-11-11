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

class RandomGenerator {
    private:
    std::random_device m_rnd;
    std::seed_seq m_seeds;
    std::mt19937 m_mt_rand;
    public:
    RandomGenerator();
    int rnd(int min, int max);
    // friend class DeckShuffle;
};

class DeckShuffle {
    private:
    public:
    DeckShuffle(){}
    void print_random_number(RandomGenerator r)
    {
        std::cout << r.rnd(1, 52) << "\n";
    }
    int generate_number(std::mt19937 rnd, int min, int max)
    {
            return std::uniform_int_distribution { min, max }(rnd);
    }

};


#endif
