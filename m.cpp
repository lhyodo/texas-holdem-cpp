#include <iostream>
#include <string>
#include <vector>

#include "Card.cpp"
#include "Dealer.cpp"
#include "QuickSort.cpp"
int main() {
  Dealer dealer{};

  // player initialization
  std::vector<Player> vect_of_players{};
  vect_of_players.push_back(Player());  // you
  vect_of_players.push_back(Player());  // computer
  vect_of_players.push_back(Player());  // computer
  vect_of_players[0].name = "You";
  vect_of_players[1].name = "Computer1";
  vect_of_players[2].name = "Computer2";
  vect_of_players[0].next = &vect_of_players[1];
  vect_of_players[1].next = &vect_of_players[2];
  vect_of_players[2].next = &vect_of_players[0];

  // your index in vect_of_players
  Player *me = &vect_of_players[0];

  // check, call, raise #, fold
  std::string input{};

  // blinds initialization
  int round_counter = 1;  // blinds increase every 5 rounds
  dealer.small_blind_value = 50;
  dealer.big_blind_value = 100;
  dealer.current_bet = dealer.big_blind_value;
  Player *small_blind = &vect_of_players[0];
  Player *big_blind = &vect_of_players[1];
  Player *starter = &vect_of_players[2];

  for (auto i = 0; i < 100; ++i) {  // max 100 rounds

    for (auto j = vect_of_players.begin(); j != vect_of_players.end(); ++j) {  // initialize pots and fill hands
      j->pot = 0;
      j->active_bettor = true;
      j->all_in = false;
      dealer.fillHand(*j);
    }

    me->displayHand();  // display your hand

    // take blinds
    if (small_blind->chips <= dealer.small_blind_value) {  // small blind
      small_blind->pot = small_blind->chips;
      small_blind->chips = 0;
      small_blind->all_in = true;
    } else {
      small_blind->pot = dealer.small_blind_value;
      small_blind->chips -= dealer.small_blind_value;
    }
    if (big_blind->chips <= dealer.big_blind_value) {  // big blind
      big_blind->pot = big_blind->chips;
      big_blind->chips = 0;
      big_blind->all_in = true;
    } else {
      big_blind->pot = dealer.big_blind_value;
      big_blind->chips -= dealer.big_blind_value;
    }

    // start bets
    Player *it = starter;  // iterator
    std::cout << "enter call, fold, or quit: ";
    std::cin >> input;
    if (input == "call") {
      if (it == small_blind) {
        if (it->chips <= dealer.current_bet - dealer.small_blind_value) {
          it->pot = it->chips;
          it->chips = 0;
          it->all_in = true;
        }
        if (it->chips > dealer.current_bet - dealer.small_blind_value) {
          it->pot += dealer.current_bet - dealer.small_blind_value;
          it->chips -= dealer.current_bet - dealer.small_blind_value;
        }
      }

    } else if (input == "fold") {
      it->active_bettor = false;
    }
    it = it->next;
    while (it != starter) {
    }
  }

  return 0;
}