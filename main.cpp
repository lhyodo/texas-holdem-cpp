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

  // check, call, raise, fold
  std::string input{};
  while (input != "quit") {
    
    dealer.fillHand(vect_of_players[0]);
    dealer.fillHand(vect_of_players[1]);
    std::cout << "Your Hand: " << std::endl;
    dealer.displayHand(vect_of_players[0]);
    // flop
    std::cout << "enter 'check', 'call', 'raise #', 'fold', or 'quit': ";
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
    std::cout << "enter 'check', 'call', 'raise #', 'fold', or 'quit': ";
    std::cin >> input;
    if (input == "check") {
      dealer.displayTurn();
    }
    if (input == "quit") {
      break;
    }
    if (input == "fold") {
      continue;
    }

    // river
    std::cout << "enter 'check', 'call', 'raise #', 'fold', or 'quit': ";
    std::cin >> input;
    if (input == "check") {
      dealer.displayRiver();
      std::cout << "Computer had:" << std::endl;
      dealer.displayHand(vect_of_players[1]);
      int player_points = dealer.assignPoints(vect_of_players[0]);
      int computer_points = dealer.assignPoints(vect_of_players[1]);
      std::cout << "Player has point value of " << player_points << "." << std::endl;
      std::cout << "Computer has point value of " << computer_points << "." << std::endl;
      if (player_points < computer_points) {
        std::cout << "You lose." << std::endl;
      }
      if (player_points > computer_points) {
        std::cout << "You win." << std::endl;
      }
      if (player_points == computer_points) {
        std::cout << "Tie." << std::endl;
      }
      
      std::cout << "============================\n";
      continue;
    }
    if (input == "quit") {
      break;
    }
    if (input == "fold") {
      std::cout << "============================\n";
      continue;
    }
  }

  // if (dealer.isPair(vect_of_players[0])) {
  //   std::cout << "You have a pair!\n";
  // }

  return 0;
}