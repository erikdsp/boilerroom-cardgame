#ifndef DECK_H
#define DECK_H
#include <random>
#include <stack>
#include <vector>

enum Suits {
    HEARTS,
    CLUBS,
    DIAMONDS,
    SPADES
};

enum Values{
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
    const Suits suit;
    const Values value;

    public:
    Card(Suits suit_in, Values value_in);
    constexpr int get_val() const;   
};

class BlackjackCard : Card {
    public:
    std::vector<int> values();
};

class DeckShuffler {
    private:
    std::mt19937 mt;

    public:
    DeckShuffler();
    DeckShuffler(uint32_t seed);
};

class Deck {
    private:
    std::stack<Card> cards;
    
    public:
    Deck();
    Deck(std::vector<Card> &deck);
    Card draw();
    void shuffle(DeckShuffler &);
};




#endif