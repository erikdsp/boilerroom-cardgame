#include <iostream>
#include "Player.h"

Player::Player() : purse{200}, name{}{
    std::cout << "Enter your name: ";
    std::cin >> name;
}

Player::Player(std::string name_in, double initial) :
    name{std::move(name_in)}, purse{initial}{

}

double Player::debit(double amount){
    if( purse < amount ){
        throw std::runtime_error("Not enough funds");
    }
    purse -= amount;
    return amount;
}

void Player::credit(double amount){
    purse += amount;
}

bool Player::can_pay(double amount) const {
    return purse >= amount;
}

bool Player::surrender(){
    char selection {};
    std::cout   << "Do you wish to surrender this bid?" << '\n' 
                << "You will be credited half your bet." << '\n'
                << "y/n -> ";
    std::cin    >> selection;
    return selection == 'y';
}

bool Player::split(){
    char selection {};
    std::cout   << "Do you wish to split this deal?" << '\n' 
                << "You will need to pay the same bid for the second deal." << '\n'
                << "y/n -> ";
    std::cin    >> selection;
    return selection == 'y';
}

bool Player::double_down(){
    char selection {};
    std::cout   << "Do you wish to double down?" << '\n' 
                << "You will double your bet but only get one more card." << '\n'
                << "y/n -> ";
    std::cin    >> selection;
    return selection == 'y';
}

bool Player::hit(){
    char selection {};
    std::cout   << "Do you wish to hit?" << '\n' 
                << "You will add a card to your deal." << '\n'
                << "y/n -> ";
    std::cin    >> selection;
    return selection == 'y';

}

std::ostream& operator<<(std::ostream& os, const Player& p ){
    os << p.name;
    return os;
}