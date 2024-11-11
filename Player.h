#ifndef CHAS_BLACKJACK_PLAYER_H
#define  CHAS_BLACKJACK_PLAYER_H

#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

#include "Deck.h"

class Deal {
    private:
    const Player& player;
    std::vector<BlackjackCard> cards; 
    
    public:
    Deal(Player&, BlackjackCard card);
    Deal(Player&);
    void add_card( BlackjackCard card );
    int min_sum() const;
    int max_sum() const;
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