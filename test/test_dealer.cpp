#define CATCH_CONFIG_MAIN
#include "../Deck.h"
#include "catch.hpp"

/* SCENARIO ("The dealer deals a card to a destination"){
    Deal destination {};
    CardDealer dealer;
    GIVEN ("There is one card, 9 spades in the shoe") {
        dealer.replace_shoe(std::vector<Card> { {3, 9} });
        WHEN("The dealer deals the card") {
            dealer.deal(destination);
            THEN ("There is no card in the shoe and we have dealt a 9 of spades "){
                CHECK_THROWS(dealer.draw_card());
                REQUIRE(destination.min_value() == 9);
            }
        }
    }
} */

SCENARIO ("A play round is started"){
    GIVEN ("A player has enough money for at least starting bid"){
        WHEN ("The player chooses at least one position to start a bet"){
            THEN ("The player places the starting bid on the betting box"){

            }
        }
    }
}

SCENARIO ("Initial deal"){
    GIVEN ("There are starting bids in at least one betting box"){
        WHEN ("The dealer deals the cards to the betting boxes with bids"){
            THEN ("One card is dealt to each box and then the house, then one more to each box"){

            }
        }
    }
}

SCENARIO ("Natural blackjack"){
    GIVEN ("The cards in a betting box total to 21"){
        WHEN ("The dealer gives the house deal a second card"){
            THEN ("If the house has a natural blackjack, the house wins, otherwise the bet wins 3:2"){

            }
        }
    }
}


SCENARIO ("A split"){
    GIVEN ("A player's starting deal has two cards with the same face value and the player can afford two starting bids"){
        WHEN ("They choose to split"){
            THEN ("Each of the cards in the start deal become the first card in a new deal, and the starting bid amount is placed on both bids"){

            }
        }
    }
}



SCENARIO ("Deal"){
    GIVEN ("It is the player's turn and they have not previously chosen to stand"){
        WHEN ("The player choses to deal"){
            THEN ("An additional card is dealt to their hand"){

            }
        }
    }
}


SCENARIO ("Double down"){
    GIVEN ("The player has not chosen to stand and has enough money to double their bet on a position"){
        WHEN ("The player adds an additional wager to the bet"){
            THEN ("An additional card is dealt to their hand"){

            }
        }
    }
}


SCENARIO ("Hand going bust"){
    GIVEN ("A card is dealt to a hand"){
        WHEN ("The minumum value of the hand is above 21"){
            THEN ("The hand is bust and the position lost"){

            }
        }
    }
}


SCENARIO ("Bets settled"){
    GIVEN ("All positions stand"){
        WHEN ("A player has a higher value than the house"){
            THEN ("The position pays out 1.5x"){

            }
        }
    }
}