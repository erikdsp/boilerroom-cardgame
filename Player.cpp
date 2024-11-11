#include "Player.h"

Deal::Deal(Player& player) : 
    player{player} {

}

Deal::Deal(Player& player, BlackjackCard card) :
    player{player},
    cards{std::move(card)}
{

}

int Deal::min_sum() const{
    int sum = {};
    for (BlackjackCard c : cards){
        sum += std::ranges::min(c.values());
    }
    return sum;
}

int Deal::max_sum() const{
    int sum = {};
    for (BlackjackCard c : cards){
        sum += std::ranges::max(c.values());
    }
    return sum;
}

void Deal::add_card( BlackjackCard card ){
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