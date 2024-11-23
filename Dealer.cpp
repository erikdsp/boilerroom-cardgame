#include <exception>
#include "Dealer.h"

/*
 -- CARD --
*/

/*
 -- DEAL --
*/

Deal::Deal() : cards{} {

}

Deal::Deal(Card card) : cards{{std::move(card)}}{

}

void Deal::add_card(Card c){
    cards.push_back(c);
}

std::vector<Card> Deal::empty(){
    return std::move(cards);
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

int Deal::size() const{
    return cards.size();
}

bool Deal::splittable() const{
    if( cards.size() == 2 ){
        if( cards.front().value() == cards.back().value() ){
            return true;
        }
    }
    return false;
}


Deal& operator+= (Deal& lhs, Card& rhs){
    lhs.add_card(rhs);
    return lhs;
}

/*
 -- DECK --
*/

Deck::Deck() : gen{std::random_device{}()}{

}

Deck::Deck(std::vector<Card> in) : 
    gen{std::random_device{}()}, 
    cards {in}{

}

Card Deck::draw(){
    if (size() < 1){
        throw std::runtime_error("Drawing from empty deck");
    }

    Card r_card = std::move(cards.back());
    cards.pop_back();

    return r_card;
}

void Deck::add_cards(std::vector<Card> in){
    cards.insert(cards.end(), in.rbegin(), in.rend());
}

int Deck::size() const {
    return cards.size();
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), gen);
}

/*
 -- CARDDEALER --
*/

CardDealer::CardDealer() : 
    shoe{},
    discard{} {

}

void CardDealer::reshuffle(std::vector<Card> in){
    shoe.add_cards(std::move(in));
}

void CardDealer::deal(Deal& current_deal){
    current_deal.add_card(shoe.draw());
}

void CardDealer::discard_deal(std::vector<Card> in){
    discard.insert(discard.end(), in.begin(), in.end());
}

int CardDealer::discard_size() const {
    return discard.size();
}