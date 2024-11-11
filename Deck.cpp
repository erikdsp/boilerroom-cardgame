#include "Deck.h"
#include <iostream>
#include <stack>

/** 
 * Standard constructor 
 */
Card::Card(Suits suit, Values value)
    : m_suit{suit}, m_value{value}{}

/** 
 * @return Value of the card
 */
Values Card::get_value()
{
    return m_value;  
}

/** 
 * @return Suit of the card
 */
Suits Card::getsuit()
{
    return m_suit;
}


/**  
 * Constructor that creates a standard deck of 52 cards
 * 
 */
Deck::Deck()
{
    for (int i = 0 ; i < 52 ; i++)
    {
       m_cards.push_back({static_cast<Suits>(i/13),static_cast<Values>((i%13)+1)});   
    }
}

/**  
 * Constructor that copies an already created deck into m_cards
 * @param deck reference to vector<Card> deck
 */
Deck::Deck(std::vector<Card>& deck)
    : m_cards{deck} {}


RandomGenerator::RandomGenerator()
    : m_rnd {std::random_device {}}, m_seeds {m_rnd(), m_rnd(), m_rnd(), m_rnd()}, m_mt_rand{m_seeds}
{
    // std::random_device rnd{};
	// std::seed_seq seeds{ rnd(), rnd(), rnd(), rnd(), rnd(), rnd(), rnd(), rnd() }; // seed with 8 random integers from std::random_device
	// std::mt19937 mt_rand{ seeds }; // initialize Mersenne Twister with the std::seed_seq
    // m_mt_rand = mt_rand;
}

int RandomGenerator::rnd(int min, int max)
{
    return std::uniform_int_distribution { 1, 52 }(m_mt_rand);
}