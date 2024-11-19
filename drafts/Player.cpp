#include <algorithm>
#include <numeric>
#include <iostream>
#include "Player.h"

Deal::Deal(Player& player) : 
    player{player} {

}

Deal::Deal(Player& player, Card& card) :
    player{player},
    cards{std::move(card)}
{

}

int Deal::sum() const{
    int sum = std::accumulate(cards.begin(), cards.end(), int{0});
    return sum;
}

void Deal::add_card( Card& card ){
    cards.emplace_back(std::move(card));
}

bool Deal::play() const{
    return this->player.hit_or_stand();
}


Player::Player() :
    name {"Guest"}, purse {200.0} {
}

Player::Player(std::string name, double buyin) : 
    name{std::move(name)}, 
    purse{buyin} {

}

double Player::bid(double min, double max) {
    double input {};
    
    do
    {
        std::cin >> input;
    } while ( input > purse || input < min );

}

bool Player::hit_or_stand() const {
    bool input {};

    enum Choices {
        STAND,
        HIT
    };

    do
    {
        std::cin >> input;
    } while ( input == STAND || input == HIT );

    return input;
}