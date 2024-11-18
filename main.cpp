#include "Dealer.h"
#include <iostream>

int main()
{

    // Very basic testing of shuffle_deck and draw functions
    // RandomGenerator gen();   // default contructor
    RandomGenerator gen(0);     // provide seed for deterministic shuffle
    Deck deck1{};
    deck1.add_standard_deck();
    deck1.shuffle_deck(gen.m_mt_rand);
    std::cout << deck1.draw().value << "\n";
    std::cout << deck1.draw().value << "\n";
    std::cout << deck1.draw().value << "\n";

    return 0;
}