#include "Dealer.h"

/*
 -- CARD --
*/

Card::Card(int suit_in, int value_in) 
: m_suit{ suit_in }, m_value{ value_in } {}


int Card::suit()
{
    return m_suit;
}
int Card::value()
{
    return m_value;
}

/*
 -- DEAL --
*/

Deal::Deal() : cards{} {

}

Deal::Deal(Card card) : cards{std::move(card)}{

}

Deal& Deal::add_card(Card c){
    cards.push_back(c);
    return *this;
}

int Deal::min_value() const{
    int sum {};

    for ( auto c : cards){
        if ( c.value() == 1 ){
            sum += 1;
        } else if ( c.value() > 10 ) {
            sum += 10;
        } else {
            sum += c.value();
        }
    }

    return sum;
}

int Deal::max_value() const{
    int sum {};

    for ( auto c : cards){
        if ( c.value() == 1 ){
            sum += 11;
        } else if ( c.value() > 10 ) {
            sum += 10;
        } else {
            sum += c.value();
        }
    }
    
    return sum;
}

/** 
 * -- RandomGenerator --
*/
RandomGenerator::RandomGenerator()
    : m_mt_rand{std::random_device{}()} {}


/** 
 * -- Deck --
*/
Deck::Deck() {}

// Deck::Deck() : gen{std::random_device{}()} {}

Deck::Deck(std::vector<Card> in) : 
    m_cards {in} {}


void Deck::shuffle_deck(std::mt19937 r)
{
    std::ranges::shuffle(m_cards, r);
}

// void Deck::shuffle(uint32_t) {}

Card Deck::draw(){
    return Card{3,1};
}

/** 
 * -- CardDealer --
*/
CardDealer::CardDealer() : 
    shoe{},
    discard{} {

}

void CardDealer::reshuffle(std::vector<Card> cards){
    shoe = Deck{cards};
}

Deal CardDealer::deal(){
    return Deal(shoe.draw());
}


Deal CardDealer::deal(Deal current_deal){
    Deal new_deal { current_deal.add_card(shoe.draw()) };
    return new_deal;
}

Deal& operator+= (Deal& lhs, Card& rhs){
    return lhs.add_card(rhs);
}