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
  std::cout << "please enter 'check', 'call', 'raise ##', or 'fold': ";
  std::string input{};
  std::cin >> input;

  if (input == "check") {
    dealer.fillBoard();
    dealer.displayFlop();
  } else if (input == "fold") {
    dealer.resetDeck();
    dealer.fillHand(vect_of_players[0]);
    dealer.fillHand(vect_of_players[1]);
    dealer.displayHand(vect_of_players[0]);
  }

  // if (dealer.isPair(vect_of_players[0])) {
  //   std::cout << "You have a pair!\n";
  // }

  return 0;
}