#include "Player.h"
#include <iostream>
// #include <algorithm>
// #include <numeric>



Player::Player() 
    : m_name {"Guest"}, m_purse {200.0} {}

Player::Player(std::string name, double buyin) 
    : m_name{name}, m_purse{buyin} {}


BlackjackSeat::BlackjackSeat(Player player, Card card)
{

}

BlackjackSeat::BlackjackSeat(Player player)
{

}

bool BlackjackSeat::make_move()
{
    return true;    // dummy return
}




// double Player::bid(double min, double max) {
//     double input {};
    
//     do
//     {
//         std::cin >> input;
//     } while ( input > purse || input < min );

// }

// bool Player::hit_or_stand() const {
//     bool input {};

//     enum Choices {
//         STAND,
//         HIT
//     };

//     do
//     {
//         std::cin >> input;
//     } while ( input == STAND || input == HIT );

//     return input;
// }


// Deal::Deal(Player& player) : 
//     player{player} {

// }

// Deal::Deal(Player& player, Card& card) :
//     player{player},
//     cards{std::move(card)}
// {

// }

// int Deal::sum() const{
//     int sum = std::accumulate(cards.begin(), cards.end(), int{0});
//     return sum;
// }

// void Deal::add_card( Card& card ){
//     cards.emplace_back(std::move(card));
// }

// bool Deal::play() const{
//     return this->player.hit_or_stand();
// }


