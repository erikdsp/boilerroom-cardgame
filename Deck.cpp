#include "Deck.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <stack>

Card::Card(Suits suit_in, Values value_in)
    : suit{suit_in}, value{value_in}{}

constexpr int Card::get_val() const{
    return value;
}

std::vector<int> BlackjackCard::values(){
    std::vector<int> card_value {};
    if ( this->get_val() == ACE){
        card_value.emplace_back(1);
        card_value.emplace_back(11);
    } else if ( this->get_val() > TEN ){
            card_value.emplace_back(10);
    } else {
            card_value.emplace_back(this->get_val());
    }
}

DeckShuffler::DeckShuffler() : mt{std::random_device{}()} {

}

DeckShuffler::DeckShuffler(uint32_t seed) : mt({seed}){

}

Deck::Deck(std::vector<Card> &deck)
    : cards(deck.begin(), deck.end()){}

Deck::Deck(){
    for ( int s {0}; s < 4; s++ ){
        for ( int v {ACE}; v <= KING; v++ ){
            cards.emplace(Card{
                static_cast<Suits>(s), 
                static_cast<Values>(v)
                });
        }
    }
}

Card Deck::draw(){
    Card card = cards.top();
    cards.pop();
    return card;
}

void Deck::shuffle( DeckShuffler& shuffler ){
    std::vector<Card> tmp;

    while ( !cards.empty() ){
        tmp.emplace_back(cards.top());
        cards.pop();
    }

    std::ranges::shuffle( tmp, shuffler );

    for( Card c : tmp ){
        cards.push(c);
    }
}