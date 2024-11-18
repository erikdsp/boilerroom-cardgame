#include "Dealer.h"

/*
 -- CARD --
*/

Card::Card(int suit_in, int value_in) : m_suit{suit_in}, m_value{value_in},
    suit{m_suit}, value{m_value}{
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
        if ( c.value == 1 ){
            sum += 1;
        } else if ( c.value > 10 ) {
            sum += 10;
        } else {
            sum += c.value;
        }
    }

    return sum;
}

int Deal::max_value() const{
    int sum {};

    for ( auto c : cards){
        if ( c.value == 1 ){
            sum += 11;
        } else if ( c.value > 10 ) {
            sum += 10;
        } else {
            sum += c.value;
        }
    }
    
    return sum;
}

Deck::Deck() : gen{std::random_device{}()}{

}

Deal CardDealer::deal(Deal current_deal){
    Deal new_deal { current_deal.add_card(shoe.draw()) };
    return new_deal;
}

Deal& operator+= (Deal& lhs, Card& rhs){
    return lhs.add_card(rhs);
}