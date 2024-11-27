#include <iostream>
#include <algorithm>
#include "Game.h"

std::ostream& operator<<(std::ostream& os, const Bet& b ){
    os << *b.player_m << ": $" <<  b.stake_m;
    return os;
}

Game::Game() : house{}, dealer{}, spots{{}, {}, {}, {}, {}, {}, {}},
                bets{}, 
                minimum_bet{20.0}, 
                minimum_raise{5.0},
                hand_limit{100.0} {
    int decks = 1;
    std::vector<Card> cards_in{};
    cards_in.reserve(52*decks);

    for (int deck = 1; deck <= decks; deck++){
        for ( int suit = 1; suit <= 4; suit++){
            for (int value = 1; value < 14; value++){
                cards_in.emplace_back(Card {suit, value});
            }
        }
    }
    dealer.reshuffle(std::move(cards_in));
}

void Game::join_game(Player* new_player){
    bool done_betting {false};

    while ( new_player->can_pay(minimum_bet) && !done_betting ){
        std::cout << "Choose a spot to join at (0 to finish):" << '\n' ;

        int spot_index {};
        std::vector<int> open_spots {};

        for (const auto& spot : spots){
            std::cout << spot_index+1 << ": ";
            auto bet = std::find_if( 
                        bets.begin(), 
                        bets.end(), 
                        [&](const Bet& d) {return d.deal_m == &spot;});

            if ( bet != bets.end() ){
                std::cout << *bet << '\n';
            } else {
                std::cout << "OPEN: $" << minimum_bet << " to join." << '\n';
                open_spots.push_back(spot_index);
            }
            spot_index++;
        }

        int input {-1};
        while ( input < 0 ) {    
            std::string in_buf{};
            std::cout << ">> ";
            std::getline(std::cin, in_buf);

            input = in_buf[0]-'0';

            if ( (input > 0 && input <= 7 ) 
                    && std::find(
                        open_spots.begin(), 
                        open_spots.end(), 
                        input-1 ) 
                        != open_spots.end()){
                std::cout << "Welcome to spot " << input << " " << *new_player << "!" << '\n';
                auto bet_it = spots.begin()+(input-1);
                bets.emplace_back( Bet (*bet_it, *new_player, new_player->debit(minimum_bet)) );
            } else if (input == 0) {
                done_betting = true;
            } else {
                std::cout << "Please enter a valid option." << '\n' ;
            }
        }
    }

    return;
}

void Game::run(){
    //Empty game early return
    if(bets.size() < 1){
        std::cout << "No bets placed.";
        return;
    }

    //Initial deal, one to each player, then the house, then one more to each player.
    for (auto bet : bets ){
        dealer.deal(*bet.deal_m);
    }
    dealer.deal(house);
    std::cout << "House has: " << house << '\n';
    for (auto bet : bets ){
        dealer.deal(*bet.deal_m);
        std::cout << *bet.player_m << " has " << *bet.deal_m << '\n';
    }

    // Ask the players for their actions
    check_blackjack();
    surrendering();
    splitting();
    doubling_down();
    hitting();
    resolve_bets();
    dealer.discard_deal(house.empty());
}

void Game::cleanup_bets(){
    std::string reason {};

    auto del = std::find_if( 
            bets.begin(), 
            bets.end(), 
            [&](Bet& b) 
                {return b.surrender() == true || b.bust() == true || b.blackjack() == true;});
    while ( del != bets.end() ){
        if( (*del).surrender() ){
            reason = "surrender.";
        } else if( (*del).bust() ){
            reason = "bust.";
        } else {
            reason = "blackjack payout.";
        }
        std::cout << "Removing " << *(*del).player_m << "'s bet due to " << reason << '\n';
        bets.erase(del);
        del = std::find_if( 
            bets.begin(), 
            bets.end(), 
            [&](Bet& b) 
                {return b.surrender() == true || b.bust() == true || b.blackjack() == true;});
    }
}

void Game::check_blackjack(){
    bool has_blackjack {false};
    
    for (auto bet : bets){
        if ( bet.deal_m->max_value() == 21 ){
            bet.blackjack(true);
            has_blackjack = true;
            std::cout << *bet.player_m << " has blackjack!" << '\n';
        }
    }
    if (has_blackjack){
        dealer.deal(house);
        if(house.max_value() == 21){
            std::cout << "House has blackjack." << '\n';
            for ( auto bet : bets ){
                if (bet.blackjack()){
                    std::cout << "Push for " << bet.player_m << '\n';
                    bet.player_m->credit(bet.stake_m);
                }
                dealer.discard_deal(bet.deal_m->empty());
            }
            bets.clear();
            return;
        } else { //Payout 3:2
            for (auto bet : bets){
                if ( bet.blackjack()){
                    bet.player_m->credit(bet.stake_m*1.5);
                }
            }
        }
        cleanup_bets();
    }
}

void Game::surrendering(){    
    //SECTION: Surrendering
    for (auto bet : bets){
        std::cout << '\n' << "---" << *bet.player_m << " plays: ---" << '\n';
        std::cout << "House has: " << house << '\n';
        std::cout << "You have: " << *bet.deal_m << '\n';
        if(bet.player_m->surrender()){
            std::cout << bet.player_m << " surrendered this bet." << '\n' 
                << bet.player_m << " collect half the stake of $" << bet.stake_m << ".";
            bet.player_m->credit(bet.stake_m/2);
            dealer.discard_deal(bet.deal_m->empty());
            bet.surrender(true);
        }
    }
    cleanup_bets();
}

void Game::splitting(){
        //SECTION: Splitting
    for (auto bet : bets){
        if(bet.player_m->can_pay(bet.stake_m) && bet.deal_m->splittable()){
        std::cout << '\n' << "---" << *bet.player_m << " plays: ---" << '\n';
        std::cout << "House has: " << house << '\n';
        std::cout << "You have: " << *bet.deal_m << '\n';
            if(bet.player_m->split()){
                Deal split_deal = bet.deal_m->split();
                dealer.deal(split_deal);
                dealer.deal(*bet.deal_m);
                std::cout << "You have: " << *bet.deal_m << " and " << split_deal << '\n';
                double split_stake = bet.player_m->debit(bet.stake_m);
                Player* split_player_p = bet.player_m;
                bets.emplace_back( Bet {split_deal, *split_player_p, split_stake} );
            }
        }
    }
    cleanup_bets();
}

void Game::doubling_down(){
    // SECTION: Doubling down
    for (auto bet : bets){
        if(bet.player_m->can_pay(bet.stake_m) && bet.deal_m->size() == 2 && !bet.stands()){
            std::cout << '\n' << "---" << *bet.player_m << " plays: ---" << '\n';
            std::cout << "House has: " << house << '\n';
            std::cout << "You have: " << *bet.deal_m << '\n';
            if(bet.player_m->double_down()){
                bet.stands(true);
                bet.stake(bet.player_m->debit(bet.stake_m));
                dealer.deal(*bet.deal_m);
                std::cout << "You have doubled down with: " << *bet.deal_m << '\n';
            }
        }
    }
    cleanup_bets();
}

void Game::hitting(){
    //SECTION: Hitting
    for (auto bet : bets){
        if(!bet.stands()){
            std::cout << '\n' << "---" << *bet.player_m << " plays: ---" << '\n';
            std::cout << "House has: " << house << '\n';
            std::cout << "You have: " << *bet.deal_m << '\n';
            if(bet.player_m->hit()){
                dealer.deal(*bet.deal_m);
                std::cout << "You have: " << *bet.deal_m << '\n';
            } else {
                bet.stands(true);
                std::cout << "You stand." << '\n';
            }
        }
    }
    cleanup_bets();
}

void Game::resolve_bets(){
    dealer.deal(house);
    std::cout << "--- House plays (Stand on all 17): ---" << '\n';
    std::cout << house << '\n';

    while ( house.min_value() <= 17 || house.max_value() <= 17 ){
        dealer.deal(house);
        std::cout << "--- House plays (Stand on all 17): ---" << '\n';
        std::cout << house << '\n';
    }

    if (house.is_bust()){
        std::cout << "The house is bust. Bets pay out 1:1." << '\n';
        for (auto bet : bets){
            std::cout << *bet.player_m << " wins $" << bet.stake_m << '\n';
            bet.player_m->credit(bet.stake_m);
        }
    } else {

        std::cout << "The house has " << house << " (" << house.best_value() << ")" << '\n';

        for (auto bet : bets){
            std::cout << *bet.player_m << " has " << *bet.deal_m << " (" << bet.deal_m->best_value() << ")" << '\n';
            if ( bet.deal_m->best_value() > house.best_value() || house.is_bust() ){
                std::cout << *bet.player_m << " wins $" << bet.stake_m << '\n';
            } else {
                std::cout << *bet.player_m << " loses." << '\n';
            }
        }
    }
    for( auto bet : bets ){
        dealer.discard_deal(bet.deal_m->empty());
    }
    bets.clear();
}