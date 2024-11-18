#ifndef CHAS_BLACKJACK_DEALER_H
#define CHAS_BLACKJACK_DEALER_H

#include "CardEnums.h"
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <stack>
#include <exception>

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
    int min_value() const;      // evaluates the first ace as 1
    int max_value() const;      // evaluates the first ace as 11

    int is_bust() const;

    // for returning the cards when the deal is finished playing
    std::vector<Card> empty();
};

class RandomGenerator 
{
    public:
    std::mt19937 m_mt_rand;
    public:
    RandomGenerator();          // seeds with std::random_device
    RandomGenerator(uint32_t seed);  // provide your own seed for deterministic "shuffle"
};


class Deck{
    private:
    // container for the cards
    std::vector<Card> m_cards{};

    public:
    Deck();
    Deck(std::vector<Card>);

    // add the standard 52 cards
    void add_standard_deck();
    void add_standard_decks(int num_of_decks);

    // shuffle the current deck held in m_cards
    void shuffle_deck(std::mt19937 gen);

    // return last card from the deck
    Card draw(); // exception on empty deck

};

class CardDealer {
    private:
    Deck shoe;
    std::vector<Card> discard;  //used cards go here after being collected

    public:
    CardDealer();

    Deal deal();
    Deal deal(Deal);

    void reshuffle (std::vector<Card>);     // replace shoe with a deck of your choice

    
    void discard_deal(std::vector<Card>); // takes cards and puts them in discard
};

#endif