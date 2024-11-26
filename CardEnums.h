#ifndef CARD_ENUMS_H
#define CARD_ENUMS_H
#include <map>
#include <string>


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

    const inline std::map<int, std::string_view> value_out {
        {1, "Ace"},
        {2, "2"},
        {3, "3"},
        {4, "4"},
        {5, "5"},
        {6, "6"},
        {7, "7"},
        {8, "8"},
        {9, "9"},
        {10, "10"},
        {11, "Jack"},
        {12, "Queen"},
        {13, "King"},
    };

const inline std::map<int, std::string_view> suit_out {
        {1, "Clubs"},
        {2, "Diamonds"},
        {3, "Spades"},
        {4, "Hearts"},
    };

} // Cards end

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
        WINNER = 2,
        BUST = 3,
        DRAW = 4
};

namespace BlackjackRules
{
    const int minimum_bid {10};     // currency is SEK

    enum HitOrStand {
        HIT,
        STAND,
        ERROR
    };

}


#endif