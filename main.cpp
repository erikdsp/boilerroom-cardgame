#include "Dealer.h"
#include <iostream>

int main()
{
    // simple test of Deal constructor
    Deal deal1{{Cards::CLUBS, Cards::ACE}};
    std::cout << deal1.get_cards().size() << "\n";

    return 0;
}