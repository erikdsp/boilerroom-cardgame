#ifndef CHAS_BLACKJACK_DEALER_H
#define CHAS_BLACKJACK_DEALER_H

#include <vector>
#include <random>
#include <ranges>
#include <algorithm>

class Card{
    private:
    int m_suit;
    int m_value;

    public:
    Card(int s, int v) : m_suit{s}, m_value{v}{}
    
    int suit() const { return m_suit; }
    int value() const { return m_value; }
};

class Deal {
    private:
    std::vector<Card> cards;

    public:
    Deal();
    Deal(Card);

    void add_card(Card);
    Deal split();

    //min/max due to aces having two possible values
    int min_value() const;
    int max_value() const;

    bool is_bust() const;
    bool stands() const;
    int size() const;
    bool splittable() const;

    // for returning the cards when the deal is finished playing
    std::vector<Card> empty();
};

class Deck{
    private:
    // random number generater for the shuffling
    std::mt19937 gen;

    // container for the cards
    std::vector<Card> cards;

    public:
    Deck();
    Deck(std::vector<Card>);

    void add_cards(std::vector<Card>);

    void shuffle();
    void shuffle(uint32_t); //deterministic "shuffle"

    int size() const;

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

    void deal(Deal&);

    void reshuffle (std::vector<Card>);

    int discard_size() const;

    void discard_deal(std::vector<Card>); // takes cards and puts them in discard
};

#endif