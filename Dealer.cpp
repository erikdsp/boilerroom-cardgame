#include <exception>
#include "Dealer.h"

/*
 -- CARD --
*/

bool operator< (Card& lhs, Card& rhs){
    if ( lhs.value() > 9 && rhs.value() > 9 ){
        return false;
    } else {
        return lhs.value() < rhs.value();
    }
}

std::ostream& operator << (std::ostream& os, const Card& c){
    std::string out {};

    switch(c.m_value){
        case 0:
        out += "test";
        break;
        case 1:
        out += "Ace";
        break;
        case 11: 
        out += "Jack";
        break;
        case 12: 
        out += "Queen";
        break;
        case 13: 
        out += "King";
        break;
        default:
        out += std::to_string(c.m_value);
        break;
    }

    switch(c.m_suit){
        case 1:
        out += " of Clubs";
        break;

        case 2:
        out += " of Diamonds";
        break;

        case 3:
        out += " of Spades";
        break;

        case 4:
        out += " of Hearts";
        break;   

        default:
        out += " of test";
        break;
    }
    os << out;
    return os;
}

/*
 -- DEAL --
*/

Deal::Deal() : cards{} {

}

Deal::Deal(Card&& card) : cards{{std::move(card)}}{

}

void Deal::add_card(Card&& c){
    cards.push_back(c);
}

Deal Deal::split(){
    return Deal(std::move(cards.back()));
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

int Deal::best_value() const{
    int sum {};

    int ace_carry {};
    for ( auto c : cards){
        int adj_val = c.value();
        if (adj_val > 10){
            adj_val = 10;
        }
        if (adj_val == 1){
            ace_carry += 1;
        }
        sum += adj_val;
    }
    while (sum < 21 && ace_carry > 0){
        if(sum + 10 <= 21){
            sum += 10;
            ace_carry -= 1;
        }
    }
    
    return sum;
}

bool Deal::is_bust() const{
    return min_value() > 21;
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

Deal& operator+= (Deal& lhs, Card&& rhs){
    lhs.add_card(std::move(rhs));
    return lhs;
}

std::ostream& operator<< (std::ostream& os, const Deal& d){
    std::string out {};
    switch(d.cards.size()){
        case 0:
        out = "[Empty deal]";
        os << out;
        break;

        case 1:    
        for (const auto c : d.cards){
            os << c;
        }
        break;
     
        default: 
        out = ", ";
        int t {};
        for (const auto c : d.cards){
            os << c;
            if ( ++t < d.cards.size() ){
                os << out;
            }
        }
        break;
    }
    return os;
}

/*
 -- DECK --
*/

Deck::Deck() : gen{std::random_device{}()}{

}

Deck::Deck(std::vector<Card>&& in) : 
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

void Deck::add_cards(std::vector<Card>&& in){
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

CardDealer::CardDealer(std::vector<Card>&& in) : 
    shoe{std::move(in)},
    discard{} {

}

void CardDealer::reshuffle(std::vector<Card>&& in){
    shoe.add_cards(std::move(in));
    shoe.shuffle();
}

void CardDealer::deal(Deal& current_deal){
    current_deal.add_card(shoe.draw());
}

//Takes the result of the empty() method of a deal
void CardDealer::discard_deal(std::vector<Card>&& in){
    discard.insert(discard.end(), in.begin(), in.end());
}

int CardDealer::discard_size() const {
    return discard.size();
}