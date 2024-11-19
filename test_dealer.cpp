#define CATCH_CONFIG_MAIN
#include "Dealer.h"
#include "catch.hpp"

SCENARIO ("The dealer deals a card to a destination"){
    Deal destination {};
    CardDealer dealer;
    GIVEN ("There is one card, 9 spades in the shoe") {
        dealer.replace_shoe(std::vector<Card> { {3, 9} });
        WHEN("The dealer deals the card") {
            dealer.deal(destination);
            THEN ("There is no card in the shoe and we have dealt a 9 of spades "){
                CHECK_THROWS(dealer.deal());
                REQUIRE(destination.min_value() == 9);
            }
        }
    }
}

