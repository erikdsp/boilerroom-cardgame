#include <algorithm>
#include <iostream>
#include "Player.h"

Player::Player() :
    name {"Guest"}, purse {200.0} {
}

Player::Player(std::string name, double buyin) : 
    name{std::move(name)}, 
    purse{buyin} {

}

double Player::bid() {
    double input {};
    
    do
    {
        std::cin >> input;
    } while ( input > purse || input < 1 );

}

bool Player::hit_or_stand(Deal& deal) {
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