#include "Deck.h"
#include <iostream>
#include <random>

int main()
{
    std::random_device rnd{};
	std::seed_seq seeds{ rnd(), rnd(), rnd(), rnd(), rnd(), rnd(), rnd(), rnd() }; // seed with 8 random integers from std::random_device
	std::mt19937 mt_rand{ seeds }; // initialize Mersenne Twister with the std::seed_seq


    DeckShuffle test;
    test.print_number(mt_rand);     // funkar inte. Det blir samma varje gång
	for (int i = 0; i < 6; i++)
    {
        // std::cout << test.generate_number(mt_rand, 1, 52) << "\n";     // funkade inte
        // std::cout << std::uniform_int_distribution { 1, 52 }(mt_rand) << "\n"; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };
    }

    return 0;
}