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
    bool m_playing{true};

    public:
    Deal();         // creates an empty deal
    Deal(Card);     // creates a deal with one card
                    // do we also want a constructor with a std::vector<Card> ?

    Deal& add_card(Card);
    Deal get_deal();

    //min/max due to aces having two possible values
    int min_value() const;      // evaluates the first ace as 1
    int max_value() const;      // evaluates the first ace as 11

    bool is_bust() const;
    bool playing() const;
    void stand();

    // for testing/debugging
    std::vector<Card> get_cards();  

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

    // For CardDealer to return cards
    void add_cards(std::vector<Card>);

    // shuffle the current deck held in m_cards
    void shuffle_deck(std::mt19937 gen);

    // return last card from the deck
    Card draw(); // exception on empty deck

};

class CardDealer {
    private:
    Deck shoe;
    std::vector<Card> discard;  //used cards go here after being collected
    int m_players_in_game{};

    public:
    // constructor for empty CardDealer
    CardDealer();
    // constructor that adds n standard decks and shuffles them
    CardDealer(int num_of_decks, std::mt19937 gen);   

    // all logic about the game go into the deal functions. Renamed to draw_card()
    // Deal deal();            
    // Deal deal(Deal);
    Card draw_card();
    Card draw_card(Deal);
    void deal(Deal& d);
    bool another_card(Deal& d);
    bool game_on();

    // testing/debugging function
    void replace_shoe(std::vector<Card>);     // replace shoe with a hand of your choice

    // if we go the empty constructor way
    void add_deck_to_shoe(Deck d);

    // moves discard to shoe using add_cards() then shuffles using shuffle_deck()
    void shuffle(std::mt19937 gen);
    
    void discard_deal(std::vector<Card>); // takes cards and puts them in discard
};

#endif