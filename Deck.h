#ifndef CHAS_BLACKJACK_DEALER_H
#define CHAS_BLACKJACK_DEALER_H

#include "CardEnums.h"
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <exception>

class Card{
    public:
    int suit;
    int value;
    int card_holder;
    Card(int s, int v, int c_h);
};

class Player {
    private:
    std::string m_name;
    double m_purse;
    double current_bid{};
    bool m_playing{true};
    int m_id;               // 0 means not playing, >= 1 means playing
    public:
    Player();
    Player(std::string name, int id = 0, double purse = 1000);
    int get_id();
    std::string get_name();
};

class Deck{
    protected:
    // container for the cards, a card contains info about who holds it
    std::vector<Card> m_cards{};

    public:
    Deck();
    Deck(int num_of_decks, std::mt19937 gen);
    Deck(std::vector<Card>);

    // add the standard 52 cards
    void add_standard_deck();
    void add_standard_decks(int num_of_decks);

    // shuffle the current deck held in m_cards
    void shuffle_deck(std::mt19937 gen);

};

class BlackjackDeck : public Deck
{
    public:
    // give a card a player id
    void draw_card(int id); // exception on empty deck?
    int min_value(int player_id) const;      // evaluates the first ace as 1
    int max_value(int player_id) const;      // evaluates the first ace as 11
    bool is_bust(int player_id) const;
    void clear_the_table();
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
    std::random_device m_rd;
    std::seed_seq m_sese;
    std::mt19937 m_mt_rand;
    public:
    RandomGenerator();          // seeds with std::random_device
    RandomGenerator(uint32_t seed);  // provide your own seed for deterministic "shuffle"
};





#endif