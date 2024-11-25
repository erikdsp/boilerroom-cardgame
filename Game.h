#ifndef CHAS_BLACKJACK_H
#define CHAS_BLACKJACK_H

#include "Player.h"
#include "Dealer.h"

class Bet{
    private:
    bool stand_m;
    bool surrender_m;
    bool blackjack_m;

    public:
    Deal* deal_m;
    Player* player_m;
    double stake_m;

    Bet(Deal &d_in, Player &p_in, double stake) : 
        deal_m{&d_in}, player_m{&p_in}, stake_m{stake}, surrender_m{false}, blackjack_m{false}, stand_m{false} {}
    
    friend std::ostream& operator <<(std::ostream&, const Bet&);

    void stake(double money){
        stake_m += money;
    }

    bool stands(bool stand = false){
        if (stand == true){
            stand_m = true;
            return stand_m;
        } else {
            return stand_m;
        }
    }

    bool surrender(bool surrender = false ){
        if (surrender == true){
            surrender_m = true;
            return surrender_m;
        } else {
            return surrender_m;
        }
    }

    bool bust(){
        return deal_m->is_bust();
    }

    bool blackjack( bool blackjack = false ){
                if (blackjack == true){
            blackjack_m = true;
            return blackjack_m;
        } else {
            return blackjack_m;
        }
    }
};

class Game{
    private:
    Deal house;
    CardDealer dealer;
    std::vector<Deal> spots;
    std::vector<Bet> bets;
    double minimum_bet;
    double minimum_raise;
    double hand_limit;

    public:
    Game();

    void join_game(Player*);
    void bet();
    void run();
    void cleanup_bets();

    void check_blackjack();

    void surrendering();
    void splitting();
    void doubling_down();
    void hitting();

    void resolve_bets();
};

#endif