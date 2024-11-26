#ifndef CARD_ENUMS_H
#define CARD_ENUMS_H

namespace Cards
{
    enum Suits {
        CLUBS = 1,
        DIAMONDS,
        SPADES,
        HEARTS
    };

    enum Values {
        ACE = 1,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING
    };

}

namespace CardHolder
{
    enum HolderOfCard {
        DECK = 0,
        DEALER = -1,
        DISCARD = -2
    };
}

enum class BlackjackOutcome {
        NATURAL = 1,
        WINNER,
        BUST,
        DRAW
};

namespace BlackjackRules
{
    const int minimum_bid {10};     // currency is SEK
}


#endif