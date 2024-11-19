#include "Dealer.h"
#include <iostream>

// testing. Moved to CardDealer
// bool oh_another_card(Deal& d);

int main()
{
RandomGenerator gen{};
CardDealer bj_dealer{};

Deal player1{};
Deal player2{};

if (!player1.playing())
{
    if (bj_dealer.another_card(player1))    // passing reference changes player1
    {
        bj_dealer.deal(player1);            // passing reference changes player1
    }
}

if (!player2.playing())
{
    if (bj_dealer.another_card(player2))
    {
        player2.add_card(bj_dealer.draw_card(player2.get_deal()));  // old version that sends Cards and Deals
    }
}


return 0;
}


// bool oh_another_card(Deal& d)  // passing a reference might change d
// {
//     char y_or_n;
//     std::cin >> y_or_n;     // gör while loop
//     if (y_or_n == 'y')
//     {
//         return true;
//     }
//     else
//     {
//         d.stand();
//         return false;
//     }
// }
