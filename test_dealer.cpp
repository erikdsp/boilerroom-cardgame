#define CATCH_CONFIG_MAIN
#include "Game.h"
#include "catch.hpp"

const double minimum_bid {20};


SCENARIO ("The dealer deals a card to a destination"){
    Deal destination {};
    CardDealer dealer;
    GIVEN ("There is one card, 9 spades in the shoe") {
        dealer.reshuffle(std::vector<Card> { {3, 9} });
        WHEN("The dealer deals the card") {
            dealer.deal(destination);
            THEN ("There is no card in the shoe and we have dealt a 9 of spades "){
                CHECK_THROWS(dealer.deal(destination));
                REQUIRE(destination.min_value() == 9);
            }
        }
    }
}

SCENARIO ("A play round is started"){

    GIVEN ("A player has enough money for at least starting bid"){
        Player player("Player", 21.0);
        REQUIRE(player.can_pay(minimum_bid));

        WHEN ("The player chooses at least one position to start a bet"){
            Deal position{};

            THEN ("The player places the starting bid on the betting box"){
                double player_bet_amount {};
                REQUIRE_NOTHROW(player_bet_amount = player.debit(minimum_bid));
                REQUIRE(player_bet_amount == minimum_bid);
                Bet player_bet(position, player, player_bet_amount);

                REQUIRE(player_bet.stake_m == minimum_bid);
            }
        }
    }
}

SCENARIO ("Dealing the initial cards"){
    std::vector<Deal> betting_boxes {Deal()};
    Deal house;
    CardDealer dealer;
    dealer.reshuffle(std::vector<Card> { {1, 2}, {1, 1}, {1, 9} });

    Player player("Player", 21.0);
    
    GIVEN ("There are starting bids in at least one betting box"){
        std::vector<Bet> bets {{betting_boxes.front(), player, 20.0}};
        REQUIRE(bets.front().stake_m == 20.0);

        WHEN ("The dealer deals the cards"){
            for( auto b : bets ){
                REQUIRE_NOTHROW(dealer.deal(*b.deal_m));
            }
            dealer.deal(house);
            for( auto b : bets ){
                REQUIRE_NOTHROW(dealer.deal(*b.deal_m));
            }

            THEN ("Each bet has a bid with two cards, and the house has one card"){
                REQUIRE(bets.size() == betting_boxes.size());
                REQUIRE(bets.front().deal_m->size() == 2);
                REQUIRE(house.size() == 1);
            }
        }
    }
}

SCENARIO ("Natural blackjack"){

    Deal house;
    CardDealer dealer;

    double minimum_bid {20};


    GIVEN ("The cards in a betting box total to 21, and the house has a 10"){
        std::vector<Deal> betting_boxes {Deal()};

        Player player("Player", 21.0);

        std::vector<Bet> bets {{betting_boxes.front(), player, minimum_bid}};

        // Betting box setup
        betting_boxes.front().add_card({0,1});
        betting_boxes.front().add_card({0,10});
        REQUIRE(betting_boxes.front().size() == 2);
        REQUIRE(betting_boxes.front().max_value() == 21);
        
        // House setup
        house.add_card({0, 10});
        REQUIRE(house.size() == 1);
        REQUIRE(house.max_value() == 10);

        WHEN ("The dealer gives the house deal a second card, which is an ace"){
            dealer.reshuffle({{0, 1}});
            REQUIRE_NOTHROW(dealer.deal(house));

            THEN ("House has a blackjack. The house wins, and we resolve all bets"){
                REQUIRE(house.size() == 2);
                REQUIRE(house.max_value() == 21);
                for(auto b : betting_boxes){
                    dealer.discard_deal(b.empty());
                }
                dealer.discard_deal(house.empty());
                REQUIRE(dealer.discard_size() == 4);
                betting_boxes.clear();
            }
        }
    }

    GIVEN ("The cards in a betting box total to 21"){
        std::vector<Deal> betting_boxes {Deal()};
        Player player("Player", 0.0);
        std::vector<Bet> bets {{betting_boxes.front(), player, minimum_bid}};

        // Betting box setup
        betting_boxes.front().add_card({0,1});
        betting_boxes.front().add_card({0,10});
        REQUIRE(betting_boxes.front().size() == 2);
        REQUIRE(betting_boxes.front().max_value() == 21);

        // House setup
        house.add_card({0, 10});
        REQUIRE(house.size() == 1);
        REQUIRE(house.max_value() == 10);

        WHEN ("The dealer gives the house deal a second card"){
            dealer.reshuffle({{0, 2}});
            REQUIRE_NOTHROW(dealer.deal(house));

            THEN ("The blackjack hand wins 3:2, we can continue playing the other bets"){
                for (auto bet = bets.begin(); bet != bets.end(); ){
                    if( bet->deal_m->size() == 2 && bet->deal_m->max_value() == 21 ){
                        REQUIRE_FALSE(player.can_pay(30.0));
                        bet->player_m->credit(30.0);
                        REQUIRE(player.can_pay(30.0));
                        bets.erase(bet);
                    } else {
                        ++bet;
                    }
                }
            }
        }
    }
}




SCENARIO ("A split"){
    GIVEN ("A player bet has two cards with the same face value and the player can afford an additional starting bid"){
        std::vector<Deal> betting_boxes {Deal()};
        Player player("Player", minimum_bid);
        std::vector<Bet> bets {{betting_boxes.front(), player, minimum_bid}};

        //Should use dealer here
        betting_boxes.front().add_card({0,1});
        betting_boxes.front().add_card({0,1});

        // Find a splittable hand, either looping all or a while until "bet" is bettable.end()
        auto original_deal = std::find_if(
            betting_boxes.begin(), betting_boxes.end(), 
            [&](const Deal& d){return d.splittable();}); // predicate is calling member function

        //Should be true by definition
        REQUIRE(original_deal->splittable());
        REQUIRE(player.can_pay(minimum_bid));

        WHEN ("They choose to split"){

            std::stringstream yes ("y");
            std::streambuf *cinbuf = std::cin.rdbuf(); 
            std::cin.rdbuf(yes.rdbuf());
            REQUIRE(player.split());
            std::cin.rdbuf(cinbuf);

            THEN ("Each of the cards in the start deal become the first card in a new deal, and the starting bid amount is placed on both bids, and each deal gets an additional card"){
                Deal split_deal = original_deal->split();
                betting_boxes.push_back(split_deal);
                double split_stake = player.debit(minimum_bid);
                bets.emplace_back(Bet {split_deal, player, split_stake});
                
                original_deal->add_card({0,2});
                split_deal.add_card({0,2});

                //Check that the player has two bets at mimimum bid
                for(const auto b : bets){
                    REQUIRE_THAT(b.stake_m, Catch::Matchers::WithinRel(minimum_bid, 0.1));
                    REQUIRE(b.player_m == &player);
                    REQUIRE(b.deal_m->size() == 2);
                }

                //Both deals have two cards
                for(const auto d : betting_boxes){
                    REQUIRE(d.size() == 2);
                }
            }
        }
    }
}



SCENARIO ("Deal"){
    CardDealer dealer;
    dealer.reshuffle({{0,1}, {0,2}, {0,3}});

    std::vector<Deal> betting_boxes {Deal()};
    Player player("Player", minimum_bid);
    std::vector<Bet> bets {{betting_boxes.front(), player, minimum_bid}};
    auto bet = bets.front();
    dealer.deal(*bet.deal_m);
    dealer.deal(*bet.deal_m);

    GIVEN ("It is the player's turn and they have not previously chosen to stand on that bet"){
        REQUIRE_FALSE(bet.deal_m->is_bust());
        REQUIRE_FALSE(bet.stands());
        WHEN ("The player choses hit"){
            // Setting cin input buffer to stringbuffer to sidestep manual input
            std::stringstream yes ("y");
            std::streambuf *cinbuf = std::cin.rdbuf(); 
            std::cin.rdbuf(yes.rdbuf());

            REQUIRE(player.hit()); // Player choice
            
            //Resetting cin stream buffer
            std::cin.rdbuf(cinbuf);

            THEN ("An additional card is dealt to the hand the bet is on"){
                dealer.deal(*bet.deal_m);

                REQUIRE(bet.deal_m->size() == 3);
            }
        }
    }
}


SCENARIO ("Double down"){
    GIVEN ("The player has a two card deal and has enough money to double their bet on that position"){
        CardDealer dealer;
        dealer.reshuffle({{0,1}, {0,2}, {0,3}});

        std::vector<Deal> betting_boxes {Deal()};
        Player player("Player", minimum_bid);
        std::vector<Bet> bets {{betting_boxes.front(), player, minimum_bid}};
        auto bet = bets.front();
        dealer.deal(*bet.deal_m);
        dealer.deal(*bet.deal_m);

        WHEN ("The player choses to double down"){
            // Setting cin input buffer to stringbuffer to sidestep manual input
            std::stringstream yes ("y");
            std::streambuf *cinbuf = std::cin.rdbuf(); 
            std::cin.rdbuf(yes.rdbuf());

            REQUIRE(player.double_down()); // Player choice
            
            //Resetting cin stream buffer
            std::cin.rdbuf(cinbuf);

            THEN ("The player adds an additional wager to the bet and an additional card is dealt to their hand, and they stand on that hand"){
                REQUIRE(player.can_pay(bet.stake_m));
                bet.stake(player.debit(bet.stake_m));
                dealer.deal(*bet.deal_m);
                REQUIRE_THAT(bet.stake_m, Catch::Matchers::WithinRel(minimum_bid * 2, 0.01));
                REQUIRE(bet.deal_m->size() == 3);
                REQUIRE(bet.stands(true) == true);
            }
        }
    }
}


SCENARIO ("Hand going bust"){
    GIVEN ("A deal gets a third card added"){
        WHEN ("A card is dealt to a hand, making the minimum value of the hand above 21"){
            THEN ("The hand is bust and the position lost"){

            }
        }
    }
}




SCENARIO ("Bets settled"){
    GIVEN ("All positions stand"){
        WHEN ("A player has a higher value than the house"){
            THEN ("The position pays out 1x"){

            }
        }
    }
}