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

/**  
 * TODO: add error checking for std::cin
 * @param nxt_id pass by reference. On success will update caller value
 * */ 
void Player::enter_bid(int& nxt_id)
{
    int bid{0};
    int input{};
    bool test{true};
    std::cout << get_name() << ", please enter a bid (minimum 10 SEK) or 0 to opt out of game: ";
    while (std::cin >> bid)
    {
        if (bid == 0)
        {
            std::cout << m_name << " opting out of game\n";
            break;
        }
        else if (bid < BlackjackRules::minimum_bid)
        {
            std::cout << "Bid too low. Please enter a valid bid or 0: ";
            if (m_purse < bid )
            {
                std::cout << "Not enough money. \n";
                break;
            } 
        }
        else if (m_purse < bid)
        {
                std::cout << "Not enough money to bid. \n";
                break;
        }
        else
        {
            std::cout << m_name << " entering game with bid of " << bid << " SEK\n";
            m_current_bid = bid;
            m_purse -= bid;
            m_playing = true;
            m_id = nxt_id++;
            break;
        }
    }
}  

void Player::set_playing(bool b)
{
    m_playing = b;
}


// input/output function, to be called from main
BlackjackRules::HitOrStand Player::hit_or_stand()
{
    char input;
    std::cout << m_name << ": h) hit or s) stand? -> ";

    // add input checking
    while (std::cin >> input)
    {
        switch(input)
        {
            case 'h':
            return BlackjackRules::HIT;
            case 's':
            return BlackjackRules::STAND;
            default:
        }
    }
    return BlackjackRules::ERROR;
}

// update each player with outcome from BlackjackDeck::calculate_win()
int Player::score_round(BlackjackOutcome outcome)
{
    // print
    print_outcome(outcome);

    // adjust purse and bid
    int sum_to_bank{ 0 };
    if (outcome == BlackjackOutcome::NATURAL) {
        m_purse += m_current_bid * 2.5;
        m_current_bid = 0;
    } else if (outcome == BlackjackOutcome::WINNER) {
        m_purse += m_current_bid * 2;
        m_current_bid = 0;
    } else if (outcome == BlackjackOutcome::DRAW) {
        m_purse += m_current_bid;
        m_current_bid = 0;
    } else {
        sum_to_bank = m_current_bid;
        m_current_bid = 0;
    }

    return sum_to_bank;
}

// output function, to be called by score_round()
void Player::print_outcome(BlackjackOutcome outcome)
{
    std::cout << m_name << " ";
    if (outcome == BlackjackOutcome::NATURAL) {
        std::cout << "wins " << m_current_bid * 1.5 << " SEK\n";
    }
    else if (outcome == BlackjackOutcome::WINNER) {
        std::cout << "wins " << m_current_bid << " SEK\n";
    }
    else if (outcome == BlackjackOutcome::DRAW) {
        std::cout << "and house is a tie " << "\n";
    }
    else if (outcome == BlackjackOutcome::BUST) {
        std::cout << "loses the bet of " << m_current_bid << " SEK \n";
    }
    else {
        std::cout << "ERROR: print_outcome called with invalid outcome\n";
    }
}

// function for testing. Maybe useful later if we have a menu system
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
    int i = 0;
    for ( auto& card : m_cards )
    {
        if ( card.card_holder == CardHolder::DECK )
        {
            // std::cout << "draw_card(" << id << ") " << " Card no " << i << "\n";
            card.card_holder = id; 
            card_was_drawn = true;
            break;            // end loop after card is drawn
        }
        ++i;
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
    for ( const auto& c : m_cards) {
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
    for ( const auto& c : m_cards) {
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

bool BlackjackDeck::has_natural(int player_id) const
{
        int count {0};
        int sum {0};
    // loop through vector of cards
    for ( const auto& c : m_cards) {
        // loop can end when we reach first DECK card
        if ( c.card_holder == CardHolder::DECK ) break;        
        // if card matches id perform calculation
        if ( c.card_holder == player_id )
        {
            if ( c.value == Cards::ACE ){
                sum += 11;
            } else if ( c.value > 10 ) {
                sum += 10;
            } else { 
            sum += c.value;
            }
            count++;
        }
    }
    if (sum == 21 && count == 2) return true;
    else return false;
}

// output function, print the hand of player
void BlackjackDeck::print_cards(Player& player, bool dealer_hide_card) const
{
    int count { 0 };
    std::cout << player.get_name() << " has - ";
    for ( const auto& c : m_cards)
    {
        if ( c.card_holder == CardHolder::DECK )    // end loop when we reach deck
        {
            // break;
        }
        if ( c.card_holder == player.get_id() )
        {
            if ( player.get_id() == CardHolder::DEALER && dealer_hide_card && count > 0)
            {
                std::cout << "a Card Face Down\n";
                ++count;
            }
            else
            {
                std::cout << Cards::value_out.at(c.value) << " of " << Cards::suit_out.at(c.suit) << " - ";
                ++count;
            }
        }
    }
    std::cout << "\n";

    // if player print all cards
    // if dealer && game_is_on print 1 front 1 back
    // if dealer && !game_is_on print all cards
    // else print error
}      

// check player against dealer and return NATURAL, WINNER, BUST or DRAW
BlackjackOutcome BlackjackDeck::calculate_win(Player& player) const
{
    if (has_natural(player.get_id())) {
        if (has_natural(CardHolder::DEALER))
        {
            return BlackjackOutcome::DRAW;   
        }
        else 
        {
            return BlackjackOutcome::NATURAL;
        }
    } else if (is_bust(player.get_id())) {
        return BlackjackOutcome::BUST;
    } else if (is_bust(CardHolder::DEALER)) {
        return BlackjackOutcome::WINNER;
    } else {
        int player_min {min_value(player.get_id()) };
        int player_max {max_value(player.get_id()) };
        int player_opt { player_max <= 21 ? player_max : player_min };
        int dealer_min {min_value(CardHolder::DEALER)};
        int dealer_max {max_value(CardHolder::DEALER)};
        int dealer_opt { dealer_max <= 21 ? dealer_max : dealer_min };
        if (player_opt > dealer_opt) {
            return BlackjackOutcome::WINNER;
        } else if (player_opt == dealer_opt) {
            return BlackjackOutcome::DRAW;
        } else {
            return BlackjackOutcome::BUST;
        }
    }

/** 
            TODO: implement game winning logic:
            // if player is bust, bid lost       (current_bid = 0)
            // if dealer is bust - standing players adds bid    (purse += current_bid * 2, current_bid = 0)
            // if player > dealer players get bid               (purse += current_bid * 2, current_bid = 0)
            // if player < dealer nothing                       (current_bid = 0)
            // if player == dealer, bid is returned             (purse += current_bid, current_bid = 0)
 */


}

// function to prepare deck for next round
void BlackjackDeck::clear_the_table(std::mt19937 gen)
{
    // move all played cards to discard - set card_holder to CardHolder::DISCARD
    // check if available cards < 50 then reshuffle         (assuming 6 cards in deck)
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


