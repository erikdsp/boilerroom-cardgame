#include "Dealer.h"

/*
 -- CARD --
*/

Card::Card(int suit_in, int value_in) 
: suit{ suit_in }, value{ value_in } {}


/*
 -- DEAL --
*/

Deal::Deal() : cards{} {

}

Deal::Deal(Card card) : cards{std::move(card)}{

}

Deal& Deal::add_card(Card c){
    cards.push_back(c);
    return *this;
}

int Deal::min_value() const{
    int sum {};

    for ( auto c : cards){
        if ( c.value == 1 ){
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

    for ( auto c : cards){
        if ( c.value == 1 ){
            sum += 11;
        } else if ( c.value > 10 ) {
            sum += 10;
        } else {
            sum += c.value;
        }
    }
    
    return sum;
}

/** 
 * -- RANDOM GENERATOR --
 * Seeds the Mersenne Twister with std::random_device
*/
RandomGenerator::RandomGenerator()
    : m_mt_rand{std::random_device{}()} {}

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

/** 
 * -- CARD DEALER --
*/
CardDealer::CardDealer() : 
    shoe{},
    discard{} {

}

void CardDealer::reshuffle(std::vector<Card> cards){
    shoe = Deck{cards};
}

Deal CardDealer::deal(){
    return Deal(shoe.draw());
}


Deal CardDealer::deal(Deal current_deal){
    Deal new_deal { current_deal.add_card(shoe.draw()) };
    return new_deal;
}

Deal& operator+= (Deal& lhs, Card& rhs){
    return lhs.add_card(rhs);
}