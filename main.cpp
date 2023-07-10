#include <iostream>
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

  // your index in vect_of_players
  int me = 0;

  // check, call, raise, fold
  std::string input{};

  // blinds initialization
  int round_counter = 0;  // blinds increase every 5 rounds
  dealer.small_blind_value = 50;
  int small_blind_index = 0;
  int big_blind_index = 1;

  int starter_index{}; // the player who goes first
  if (vect_of_players.size() <= 2) {
    starter_index = 0;
  }
  if (vect_of_players.size() > 2) {
    starter_index = 1 + big_blind_index;
  }

  

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

    // increment round
    ++round_counter;

    // initialize pot to 0 and fill hands
    for (auto i : vect_of_players) {
      i.pot = 0;
      dealer.fillHand(i);
    }

    /* blinds */
    std::cout << vect_of_players[small_blind_index].name << " is the small blind.";
    std::cout << vect_of_players[big_blind_index].name << " is the big blind.";
    std::cout << vect_of_players[starter_index].name << " goes first.";
    if (round_counter % 5 == 0) {   // increase blinds every 5 rounds
      dealer.small_blind_value *= 2;
      dealer.big_blind_value = 2 * dealer.small_blind_value;
    }
    // small blind
    if (vect_of_players[small_blind_index].chips <= dealer.small_blind_value) { // if chips are below or equal to small blind value, set chips to 0
      vect_of_players[small_blind_index].pot = vect_of_players[small_blind_index].chips;
      vect_of_players[small_blind_index].chips = 0;
    }
    if (vect_of_players[small_blind_index].chips > dealer.small_blind_value) {
      vect_of_players[small_blind_index].pot += dealer.small_blind_value;
      vect_of_players[small_blind_index].chips -= dealer.small_blind_value;
    }
    // big blind
    if (vect_of_players[big_blind_index].chips <= dealer.big_blind_value) {
      vect_of_players[big_blind_index].pot = vect_of_players[big_blind_index].chips;
      vect_of_players[big_blind_index].chips = 0;
    }
    if (vect_of_players[big_blind_index].chips > dealer.big_blind_value) {
      vect_of_players[big_blind_index].pot += dealer.big_blind_value;
      vect_of_players[big_blind_index].chips -= dealer.big_blind_value;
    }


    

    // display your hand
    dealer.displayHand(vect_of_players[0]);

    // increase blinds every 5 rounds
    
    // display



    if ((*small_blind).chips < dealer.small_blind_value) {
      // dealer.pot += (*small_blind).chips;
      (*small_blind).chips = 0;
    } else {
      // dealer.pot += dealer.small_blind_value;
      (*small_blind).chips -= dealer.small_blind_value;
    }
    if ((*big_blind).chips < (2 * dealer.small_blind_value)) {
      // dealer.pot += (*big_blind).chips;
      (*big_blind).chips = 0;
    } else {
      // dealer.pot += (*big_blind).chips;
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


    // increment blinds

  }

  // if (dealer.isPair(vect_of_players[0])) {
  //   std::cout << "You have a pair!\n";
  // }

  return 0;
}