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


/**  
 * Constructor that creates a standard deck of 52 cards
 * 
 */
Deck::Deck()
{
    for (int i = 0 ; i < 52 ; i++)
    {
       m_cards.push_back({static_cast<Suits>(i/13), (i%13)+1});   
    }
}

/**  
 * Constructor that copies an already created deck into m_cards
 * @param deck reference to vector<Card> deck
 */
Deck::Deck(std::vector<Card>& deck)
    : m_cards{deck} {}

