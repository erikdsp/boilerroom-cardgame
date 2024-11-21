#include "Deck.h"

/*
 -- CARD --
*/

Card::Card(int s, int v, int c_h = CardHolder::DECK ) 
: suit{ s }, value{ v }, card_holder { c_h } {}


/*
 -- DEAL --
*/

Deal::Deal() : cards{} {

}

// Deal::Deal(Card card) : cards{std::move(card)}{}
Deal::Deal(Card card) : cards{card} {}



Deal& Deal::add_card(Card c){
    cards.push_back(c);
    // if we use ncurses - call print function here to update screen with new card
    // if we use std::cout maybe also here but print all cards
    // if (is_bust) m_playing = false;
    return *this;
}

int Deal::min_value() const{
    int sum {};

    for ( auto c : cards) {
        if ( c.value == Cards::ACE ){
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

    for ( auto c : cards) {
        bool counted_one_ace{false};
        if ( c.value == Cards::ACE && counted_one_ace ){
            sum += 1;
        } else if ( c.value == Cards::ACE ){
            sum += 11;
            counted_one_ace = true;
        } else if ( c.value > 10 ) {
            sum += 10;
        } else {
            sum += c.value;
        }
    }
    
    return sum;
}

bool Deal::is_bust() const
{
    if (min_value() > 21) return true;
    else return false;
}

bool Deal::playing() const
{
    return m_playing;
}

void Deal::stand()
{
    m_playing = false;
}

// for testing/debugging
std::vector<Card> Deal::get_cards() 
    {
        return cards;
    }

/** 
 * -- RANDOM GENERATOR --
 * Seeds the Mersenne Twister with std::random_device
*/
RandomGenerator::RandomGenerator()
    : m_rd{}, m_sese{m_rd(), m_rd()}, m_mt_rand{std::random_device{}()} {}

/** 
 * Seeds the Mersenne Twister with a seed of your choice
*/
RandomGenerator::RandomGenerator(uint32_t seed)
    : m_mt_rand{seed} {}



/** 
 * -- DECK --
*/
Deck::Deck() {}

Deck::Deck(std::vector<Card> in) : 
    m_cards {in} {}


/**  
 * Adds the standard 52 cards to the deck
 */
void Deck::add_standard_deck()
{
    for (int i = 0 ; i < 52 ; ++i)
    {
       m_cards.push_back({(i/13)+1,(i%13)+1});   
    }
}

/**  
 * Adds several standard 52 card decks to the deck
 * @param num_of_decks
 */
void Deck::add_standard_decks(int num_of_decks)
{
    if (num_of_decks > 0)
    {    
        for (int k = 0 ; k < num_of_decks ; ++k)
        {
            add_standard_deck();
        }
    }
    else
    {
        std::cerr << "Trying to add 0 or negative number of decks\n";
    }
}

/**  
 * Shuffles the deck held in m_cards
 * @param r random generator
 */
void Deck::shuffle_deck(std::mt19937 r)
{
    std::ranges::shuffle(m_cards, r);
}

// void Deck::shuffle(uint32_t) {}

/** 
 * Draw the last card from the deck and remove it from m_cards
 * @return Card
*/
Card Deck::draw(){
    if (m_cards.size() == 0)
    {
        throw std::out_of_range("Trying to draw card from empty vector");
    }
    Card tmp = m_cards.back();      
    m_cards.pop_back();             
    return tmp;
}