#ifndef CHAS_BLACKJACK_PLAYER_H
#define  CHAS_BLACKJACK_PLAYER_H

#include "Deck.h"
#include <string>
#include <vector>


class Player {
    private:
    const std::string m_name;
    double m_purse;

    public:
    Player();
    Player(std::string, double);
    bool hit_or_stand() const;
    double bid(double min, double max);
};

class BlackjackSeat {
    private:
    const Player m_player;
    std::vector<Card> m_cards; 
    
    public:
    BlackjackSeat(Player player, Card card);
    BlackjackSeat(Player player);

    bool make_move();   
    void add_card(Card card);       
    // void add_card( Card& );
    // int sum() const;
    // bool play() const;
};

class BlackjackDealer 
{
    private:
    std::vector<Card> m_cards;
    Card m_facedown;

    public:
    void show_facedown();
    void add_card(Card card);       
};





/* 
class Deal {
    private:
    const Player& player;
    std::vector<Card> cards; 
    
    public:
    Deal(Player&, Card& card);
    Deal(Player&);
    void add_card( Card& );
    int sum() const;
    bool play() const;
};
 */



#endif