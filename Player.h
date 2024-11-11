#ifndef CHAS_BLACKJACK_PLAYER_H
#define  CHAS_BLACKJACK_PLAYER_H

#include <string>
#include <vector>
#include "Deck.h"

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

class Player {
    private:
    double purse;
    const std::string name;

    public:
    Player();
    Player(std::string, double);
    bool hit_or_stand() const;
    double bid(double min, double max);
};

#endif