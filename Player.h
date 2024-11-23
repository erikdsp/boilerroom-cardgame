#ifndef CHAS_BLACKJACK_PLAYER_H
#define  CHAS_BLACKJACK_PLAYER_H

#include <string>

class Player {
    private:
    double purse;
    std::string name;

    public:
    Player();
    Player(std::string, double);
    
    double debit(double);
    void credit(double);
    bool can_pay(double amount) const;

    bool surrender();
    bool split();
    bool double_down();
    bool hit();
};

#endif