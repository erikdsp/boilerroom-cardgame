#include "Deck.h"
#include <iostream>
#include <stack>

/** 
 * Standard constructor 
 */
Card::Card(Suits suit, int value)
    : m_suit{suit}, m_value{value}{}

/** 
 * @return value int. Should probably use other data type to allow different values, example ACE equals 1 or 11?
 */
int Card::get_value()
{
    return m_value;  
}


Deck::Deck(std::vector<Card> &deck)
    : cards{deck}{}

