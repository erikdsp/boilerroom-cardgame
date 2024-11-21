#include "Deck.h"

/*
 -- CARD --
*/

Card::Card(int s, int v, int c_h = CardHolder::DECK ) 
: suit{ s }, value{ v }, card_holder { c_h } {}


/** 
 * -- PLAYER --
*/





Player::Player()
    : m_name { "Anonymous" }, m_id { 0 }, m_purse { 1000 } {}

Player::Player(std::string name, int id, double purse)
    : m_name { name }, m_id { id }, m_purse { purse } {}

int Player::get_id()
{
    return m_id;
}

std::string Player::get_name()
{
    return m_name;
}

void Player::change_name(std::string name)
{
    m_name = name;
}



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
void BlackjackDeck::draw_card(int id){
    if (m_cards.size() == 0)
    {
        throw std::out_of_range("Trying to draw card from empty vector");
    }
    // Card tmp = m_cards.back();      
    // m_cards.pop_back();             
    // return tmp;
}



int BlackjackDeck::min_value(int player_id) const{
    int sum {};

    // OBS - FUNKAR INTE ÄN
    // needs to loop through deck each time and check card_holder
    // can likely break when card_holder == 0
    for ( auto c : m_cards) {
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

int BlackjackDeck::max_value(int player_id) const{
    int sum {};

    // OBS - FUNKAR INTE ÄN
    // needs to loop through deck each time and check card_holder
    // can likely break when card_holder == 0
    for ( auto c : m_cards) {
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

bool BlackjackDeck::is_bust(int player_id) const
{
    if (min_value(player_id) > 21) return true;
    else return false;
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


