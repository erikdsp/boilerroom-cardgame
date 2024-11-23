#ifndef CHAS_BLACKJACK_H
#define CHAS_BLACKJACK_H

#include "Player.h"
#include "Dealer.h"

class Bet{
    public:
    Deal* deal_m;
    Player* player_m;
    double stake_m;

    Bet(Deal &d_in, Player &p_in, double stake) : 
        deal_m{&d_in}, player_m{&p_in}, stake_m{stake} {}
};

#endif