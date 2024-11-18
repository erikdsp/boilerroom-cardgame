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