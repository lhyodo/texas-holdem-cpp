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
  vect_of_players[0].name = "Player1";
  vect_of_players[1].name = "Computer1";
  vect_of_players[2].name = "Computer2";

  // check, call, raise, fold
  std::string input{};

  // blinds initialization
  int blind_counter = 1;  // blinds increase every 5 rounds
  dealer.small_blind_value = 50;
  Player *small_blind{};
  small_blind = &vect_of_players[0];
  Player *big_blind{};
  big_blind = &vect_of_players[1];
  Player *start{}; // the player who goes first
  start = &vect_of_players[2];
  

  while (input != "quit") {
    // debug
    // vect_of_players[0].hand[0] = 37;
    // vect_of_players[0].hand[1] = 30;
    // vect_of_players[1].hand[0] = 17;
    // vect_of_players[1].hand[1] = 29;
    // dealer.board[0] = 40;
    // dealer.board[1] = 8;
    // dealer.board[2] = 28;
    // dealer.board[3] = 32;
    // dealer.board[4] = 20;
    // end debug
    dealer.pot = 0;
    dealer.fillHand(vect_of_players[0]); // player
    dealer.fillHand(vect_of_players[1]); // computer1
    dealer.fillHand(vect_of_players[2]); // computer2
    std::cout << "Your Hand: " << std::endl;
    dealer.displayHand(vect_of_players[0]);

    // blinds
    if (blind_counter % 5 == 0) {
      dealer.small_blind_value *= 2;
    }
    std::cout << (*small_blind).name << " is the small blind.";
    std::cout << (*big_blind).name << " is the big blind.";
    std::cout << (*start).name << " goes first.";
    if ((*small_blind).chips < dealer.small_blind_value) {
      dealer.pot += (*small_blind).chips;
      (*small_blind).chips = 0;
    } else {
      dealer.pot += dealer.small_blind_value;
      (*small_blind).chips -= dealer.small_blind_value;
    }
    if ((*big_blind).chips < (2 * dealer.small_blind_value)) {
      dealer.pot += (*big_blind).chips;
      (*big_blind).chips = 0;
    } else {
      dealer.pot += (*big_blind).chips;
      (*big_blind).chips -= 2 * dealer.small_blind_value;
    }
    

    // start bet
    


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
      dealer.assignPoints(vect_of_players[0]);
      dealer.assignPoints(vect_of_players[1]);

      std::cout << "Your hand has a point value of " << vect_of_players[0].hand_points << "." << std::endl;
      std::cout << "Computer's hand has a point value of " << vect_of_players[1].hand_points << "." << std::endl;
      if (vect_of_players[0].hand_points > vect_of_players[1].hand_points) {
        std::cout << "You win." << std::endl;
      }
      if (vect_of_players[0].hand_points < vect_of_players[1].hand_points) {
        std::cout << "You lose." << std::endl;
      }
      if (vect_of_players[0].hand_points == vect_of_players[1].hand_points) {
        Player tie_winner{};
        dealer.tieBreaker(vect_of_players[0], vect_of_players[1], tie_winner);
        if (tie_winner.hand[0] == -1) {  // -1 indicates complete tie
          std::cout << "Tie." << std::endl;
        }
        if (tie_winner.equalHand(vect_of_players[0])) {
          std::cout << "You win." << std::endl;
        }
        if (tie_winner.equalHand(vect_of_players[1])) {
          std::cout << "You lose." << std::endl;
        }
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