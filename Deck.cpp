#include "Deck.h"

/*
 -- CARD --
*/

Card::Card(int s, int v, int c_h ) 
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

bool Player::is_playing()
{
    return m_playing;
}

void Player::change_name(std::string name)
{
    m_name = name;
}

// function for testing only
void Player::set_id(int id)
{
    m_id = id;
}


/** 
 * -- DECK --
*/

Deck::Deck() {}

Deck::Deck(int num_of_decks)
    : m_cards{} 
{
    add_standard_decks(num_of_decks);
}


/**  
 * Constructor adds n standard 52 cards and shuffles the deck
 * @param num_of_decks  number of decks to add
 * @param gen           a random generator, e.g. Mersenne Twister
 */
Deck::Deck(int num_of_decks, std::mt19937 gen)
    : m_cards{} 
{
    add_standard_decks(num_of_decks);
    shuffle_deck(gen);
}

/**  
 * Constructor for debugging - adds cards of your choice
 * @param cards         vector of cards
 */

Deck::Deck(std::vector<Card> cards) 
    : m_cards { cards } {}



/**  
 * Adds the standard 52 cards to the deck
 */
void Deck::add_standard_deck()
{
    for (int i = 0 ; i < 52 ; ++i)
    {
        int suit = (i/13)+1;    // gives values in the range 1-4
        int value = (i%13)+1;   // gives values in the range 1-13
        m_cards.push_back( { suit, value } );   
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

// testing
int Deck::print_cards()
{
    int count{0};
    for (auto card : m_cards)
    {
        std::cout << card.value << " " << card.suit << "\t";
        ++count;
        if (count%13 == 0)  
        {
            std::cout << "\n";
        }
    }
    return count;
}


/**  
 * Shuffles the deck held in m_cards
 * The std::ranges library contains a shuffle function, requires C++20
 * For C++11 compilers see commented out std::shuffle
 * @param r random generator
 */
void Deck::shuffle_deck(std::mt19937 r)
{
    // std::shuffle(m_cards.begin(), m_cards.end(), r);     // For C++11 compilers
    std::ranges::shuffle(m_cards, r);                       // C++20
}


/** 
 * -- BLACKJACK DECK --
*/

BlackjackDeck::BlackjackDeck() 
    : Deck(){}

BlackjackDeck::BlackjackDeck(int num_of_decks, std::mt19937 gen)
    : Deck(num_of_decks, gen) {}

BlackjackDeck::BlackjackDeck(std::vector<Card> cards)
    : Deck(cards) {}



/** 
 * Find the first DECK card 
 * and assign it to player/dealer id
 * @param id 
*/
void BlackjackDeck::draw_card(int id){
    bool card_was_drawn{ false };
    // loop through vector of cards
    for ( auto c : m_cards)
    {
        if ( c.card_holder == CardHolder::DECK )
        {
            c.card_holder = id; 
            card_was_drawn = true;
            break;            // end loop after card is drawn
        }
    }

    if (!card_was_drawn)
    {
        throw std::out_of_range(" Error: Deck not shuffled in time. No cards left with card_holder == CardHolder::DECK ");
    }

}

/**
 * Calculates the min value of a players hand
 * Evaluates all ACES as 1
 * @param player_id
 */
int BlackjackDeck::min_value(int player_id) const{
    int sum {0};

    // loop through vector of cards
    for ( auto c : m_cards) {
        // loop can end when we reach first DECK card
        if ( c.card_holder == CardHolder::DECK ) break;        
        // if card matches id perform calculation
        if ( c.card_holder == player_id )
        {
            if ( c.value == Cards::ACE ){
                sum += 1;
            } else if ( c.value > 10 ) {
                sum += 10;
            } else { 
            sum += c.value;
            }
        }
    }

    return sum;
}


/**
 * Calculates the max value of a players hand (the highest meaningful value)
 * Evaluates the first ACE as 11 and subsequent ACES as 1
 * @param player_id
 */
int BlackjackDeck::max_value(int player_id) const{
    int sum{ 0 };

    bool counted_one_ace{ false };
    // loop through vector of cards
    for ( auto c : m_cards) {
        // loop can end when we reach first DECK card
        if ( c.card_holder == CardHolder::DECK ) break;  
        // if card matches id perform calculation
        if ( c.card_holder == player_id )
        {
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
 * Seeds the Mersenne Twister with a seed sequence with 8 std::random_device
*/
RandomGenerator::RandomGenerator()
    : m_rd{}, 
      m_sese{ m_rd(), m_rd(), m_rd(), m_rd(), m_rd(), m_rd(), m_rd(), m_rd() }, 
      m_mt_rand{ m_sese } {}

/** 
 * Seeds the Mersenne Twister with a seed of your choice
*/
RandomGenerator::RandomGenerator(uint32_t seed)
    : m_mt_rand{ seed } {}


