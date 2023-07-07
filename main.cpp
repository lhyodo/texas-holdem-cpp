#include <iostream>
#include <vector>

#include "Card.cpp"
#include "Dealer.cpp"
#include "QuickSort.cpp"
int main() {
  Dealer dealer{};

  std::vector<Player> vect_of_players{};
  vect_of_players.push_back(Player());  // player
  vect_of_players.push_back(Player());  // computer
  dealer.fillHand(vect_of_players[0]);
  dealer.fillHand(vect_of_players[1]);
  dealer.displayHand(vect_of_players[0]);

  // check, call, raise, fold
  std::string input{};
  while (input != "quit") {
    // flop
    std::cout << "please enter 'check', 'call', 'raise ##', 'fold', or 'quit': ";
    std::cin >> input;
    if (input == "check") {
      dealer.fillBoard();
      dealer.displayFlop();
    }
    if (input == "quit") {
      break;
    }
    if (input == "fold") {
      dealer.fillHand(vect_of_players[0]);
      dealer.fillHand(vect_of_players[1]);
      dealer.displayHand(vect_of_players[0]);
      continue;
    }

    // turn
    std::cout << "please enter 'check', 'call', 'raise ##', 'fold', or 'quit': ";
    std::cin >> input;
    if (input == "check") {
      dealer.displayTurn();
    }
    if (input == "quit") {
      break;
    }
    if (input == "fold") {
      dealer.fillHand(vect_of_players[0]);
      dealer.fillHand(vect_of_players[1]);
      dealer.displayHand(vect_of_players[0]);
      continue;
    }

    // river
    std::cout << "please enter 'check', 'call', 'raise ##', 'fold', or 'quit': ";
    std::cin >> input;
    if (input == "check") {
      dealer.fillBoard();
      dealer.displayRiver();
      std::cout << "============================\n";
      dealer.fillHand(vect_of_players[0]);
      dealer.fillHand(vect_of_players[1]);
      dealer.displayHand(vect_of_players[0]);
    }
    if (input == "quit") {
      break;
    }
    if (input == "fold") {
      dealer.fillHand(vect_of_players[0]);
      dealer.fillHand(vect_of_players[1]);
      dealer.displayHand(vect_of_players[0]);
      continue;
    }
  }

  // if (dealer.isPair(vect_of_players[0])) {
  //   std::cout << "You have a pair!\n";
  // }

  return 0;
}