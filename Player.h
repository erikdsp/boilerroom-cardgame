#ifndef CHAS_BLACKJACK_PLAYER_H
#define  CHAS_BLACKJACK_PLAYER_H

#include <string>
#include <vector>

class Deal {
    private:
    Player& player;
    std::vector<int> cards; //std::vector<Cards>; 
    
    public:
    Deal(Player&, Card& card);
    Deal(Player&, Card& first, Card&, second);
    void add_card( Card& );
    int sum();
};

class Player {
    private:
    double purse;
    const std::string name;

    public:
    Player();
    Player(std::string, double);
    bool hit_or_stand(Deal&);
    double bid(double min, double max);
};

#endif