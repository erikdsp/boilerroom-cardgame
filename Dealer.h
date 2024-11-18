#ifndef CHAS_BLACKJACK_DEALER_H
#define CHAS_BLACKJACK_DEALER_H

#include <vector>
#include <random>

class Card{
    private:
    int m_suit;
    int m_value;

    public:
    Card(int, int);
    
    //public accessible const references to privates
    const int& suit; 
    const int& value;
};

class Deal {
    private:
    std::vector<Card> cards;

    public:
    Deal();
    Deal(Card);

    void add_card(Card);

    //min/max due to aces having two possible values
    int min_value() const;
    int max_value() const;

    int is_bust() const;

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

    void shuffle();
    void shuffle(uint32_t); //deterministic "shuffle"

    // return last card from the deck
    Card draw();

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
    
    void discard(std::vector<Card>); // takes cards and puts them in discard
};

#endif