#include "Card.cpp"
#include "Dealer.cpp"
#include "QuickSort.cpp"
#include <iostream>
#include <vector>
int main() {
  Dealer dealer{};
  dealer.fillBoard();
  dealer.displayBoard();

  std::cout << "Enter number of players: ";
  int num_of_players{};
  std::cin >> num_of_players;
  std::vector<Player> vect_of_players{};
  for (int i = 0; i < num_of_players; ++i) {
    std::cout << "Player " << i << "'s Hand: \n";
    vect_of_players.push_back(Player());
    dealer.fillHand(vect_of_players[i]);
    dealer.displayHand(vect_of_players[i]);
    if (dealer.isPair(vect_of_players[i])) {
        std::cout << "Player " << i << " has a pair!\n";
        
    }
  }

  

  

  return 0;
}