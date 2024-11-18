#ifndef CHAS_BLACKJACK_DEALER_H
#define CHAS_BLACKJACK_DEALER_H

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <stack>

class Card{
    public:
    int suit;
    int value;
    Card(int, int);
};

class Deal {
    private:
    std::vector<Card> cards;

    public:
    Deal();
    Deal(Card);

    Deal& add_card(Card);

    //min/max due to aces having two possible values
    int min_value() const;
    int max_value() const;

    int is_bust() const;

    // for returning the cards when the deal is finished playing
    std::vector<Card> empty();
};

class RandomGenerator 
{
    public:
    std::mt19937 m_mt_rand;
    public:
    RandomGenerator();
};


class Deck{
    private:
    // container for the cards
    std::vector<Card> m_cards{};

    public:
    Deck();
    Deck(std::vector<Card>);

    void add_standard_deck();
    void shuffle_deck(std::mt19937 gen);
    // void shuffle(uint32_t); //deterministic "shuffle"

    // return last card from the deck
    Card draw(); // exception on empty deck

    // for testing
    void set_seed(uint32_t);

};

class CardDealer {
    private:
    Deck shoe;
    std::vector<Card> discard;  //used cards go here after being collected

    public:
    CardDealer();

    Deal deal();
    Deal deal(Deal);

    void reshuffle (std::vector<Card>);

    
    void discard_deal(std::vector<Card>); // takes cards and puts them in discard
};

#endif