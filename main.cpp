#include "Dealer.h"
#include <iostream>

int main()
{
    RandomGenerator gen;
    Deck deck1{};
    deck1.add_standard_deck();
    deck1.shuffle_deck(gen.m_mt_rand);
    std::cout << deck1.draw().value() << "\n";
    std::cout << deck1.draw().value() << "\n";
    std::cout << deck1.draw().value() << "\n";

    return 0;
}