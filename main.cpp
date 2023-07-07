#include <iostream>
#include <vector>

#include "Card.cpp"
#include "Dealer.cpp"
#include "QuickSort.cpp"
int main() {
  Dealer dealer{};
  dealer.fillBoard();
  dealer.displayBoard();

  std::vector<Player> vect_of_players{};
  vect_of_players.push_back(Player());
  dealer.fillHand(vect_of_players[0]);
  dealer.displayHand(vect_of_players[0]);
  if (dealer.isPair(vect_of_players[0])) {
    std::cout << "You have a pair!\n";
  }

  return 0;
}