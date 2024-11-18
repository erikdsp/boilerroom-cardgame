#include "Dealer.h"
#include <iostream>

int main()
{
    RandomGenerator gen;
    Deck deck1{};
    deck1.shuffle_deck(gen.m_mt_rand);


    return 0;
}