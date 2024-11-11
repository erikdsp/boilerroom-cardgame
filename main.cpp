#include "Deck.h"
#include <iostream>
#include <random>

int main()
{
    // std::random_device rnd{};
	// std::seed_seq seeds{ rnd(), rnd(), rnd(), rnd(), rnd(), rnd(), rnd(), rnd() }; // seed with 8 random integers from std::random_device
	// std::mt19937 mt_rand{ seeds }; // initialize Mersenne Twister with the std::seed_seq

    RandomGenerator mt_rnd;
    std::cout << mt_rnd.rnd(1, 52) << "\n";
    std::cout << mt_rnd.rnd(1, 52) << "\n";
    std::cout << mt_rnd.rnd(1, 52) << "\n";
    std::cout << mt_rnd.rnd(1, 52) << "\n";
    DeckShuffle test;
    
    // test.print_random_number(mt_rnd);
    // test.print_random_number(mt_rnd);

    // test.print_number(mt_rand);     // funkar inte. Det blir samma varje gång
	for (int i = 0; i < 6; i++)
    {
        // std::cout << test.generate_number(mt_rand, 1, 52) << "\n";     // funkade inte
      
    }
    //  std::cout << std::uniform_int_distribution { 1, 52 }(mt_rand) << "\n"; 
    //  std::cout << std::uniform_int_distribution { 1, 52 }(mt_rand) << "\n"; 
    //  std::cout << std::uniform_int_distribution { 1, 52 }(mt_rand) << "\n"; 

    return 0;
}