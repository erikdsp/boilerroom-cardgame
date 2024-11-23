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
    // id of who is currently holding the card
    // values above 1 is players, other values defined in CardEnums.h
    int card_holder;        
    Card(int s, int v, int c_h = CardHolder::DECK);
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
    bool is_playing();
    void change_name(std::string name);
    void set_id(int id);   // testing only
    // bid(double amount) needs function to bid - that calls find_id_and_enter_game()
    // find_id_and_enter_game() needs function to enter game i.e. get the next free id
};

class Deck{
    protected:
    // container for the cards, a card contains info about who holds it
    std::vector<Card> m_cards;

    public:
    Deck();
    Deck(int num_of_decks);
    Deck(int num_of_decks, std::mt19937 gen);
    Deck(std::vector<Card> cards);                // for debugging only

    private:
    // add the standard 52 cards        // make this private or protected
    void add_standard_deck();
    void add_standard_decks(int num_of_decks);

    public:
    int print_cards(); // testing
    // shuffle the current deck held in m_cards
    void shuffle_deck(std::mt19937 gen);

};

class BlackjackDeck : public Deck
{
    public:
    BlackjackDeck();
    BlackjackDeck(int num_of_decks, std::mt19937 gen);
    BlackjackDeck(std::vector<Card> cards);       // for debugging only
    public:
    // give a card a player id
    void draw_card(int id); // exception on empty deck?
    int min_value(int player_id) const;      // evaluates the first ace as 1
    int max_value(int player_id) const;      // evaluates the first ace as 11
    bool is_bust(int player_id) const;
    // move all played cards to discard
    // check if available cards < 50 then reshuffle
    void clear_the_table(std::mt19937 gen);         
    
};


class RandomGenerator 
{
    private:
    std::random_device m_rd;
    std::seed_seq m_sese;
    public:
    std::mt19937 m_mt_rand;
    public:
    RandomGenerator();          // seeds with std::random_device
    RandomGenerator(uint32_t seed);  // provide your own seed for deterministic "shuffle"
};





#endif