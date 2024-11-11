#include "Deck.h"
#include <iostream>
#include <stack>
Card::Card(Suits suit_in, int value_in)
    : suit{suit_in}, value{value_in}{}
int Card::get_val(int card_value){
    
}
Deck::Deck(std::vector<Card> &deck)
    : cards{deck}{}

