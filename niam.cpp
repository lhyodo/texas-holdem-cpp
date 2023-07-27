#include <iostream>
#include <string>
#include <vector>

#include "Card.cpp"
#include "Dealer.cpp"
#include "Player.cpp"
#include "QuickSort.cpp"
int main() {
    Dealer dealer{};

    // player and linked list initialization
    dealer.addPlayer("You");
    dealer.addPlayer("BOT Frank");
    dealer.addPlayer("BOT Gary");
    dealer.initBlinds();
    dealer.setBlinds(50, 100);

    int roundCounter = 1;
    // while (dealer.getActivePlayerCount() > 1) {
    dealer.takeBlinds();
    dealer.fillHands();
    dealer.displayHand(dealer.players[0]);

    // pre flop bets
    std::string input_str{};
    Player *current = dealer.head;
    do {
        if (current->active_bettor == true) {
            if (current->name.find("BOT") != std::string::npos) {
                if (current == dealer.big_blind && dealer.current_bet == dealer.big_blind_value) {
                    std::cout << current->name << " has checked.\n";
                    // do nothing
                } else if (current == dealer.big_blind && dealer.current_bet != dealer.big_blind_value) {
                    std::cout << current->name << " has called.\n";
                    dealer.takeBet(*current, dealer.current_bet - dealer.small_blind_value);
                } else if (current == dealer.small_blind) {
                    std::cout << current->name << " has called.\n";
                    dealer.takeBet(*current, dealer.current_bet - dealer.small_blind_value);
                } else if (current != dealer.small_blind && current != dealer.big_blind) {
                    std::cout << current->name << " has called.\n";
                    dealer.takeBet(*current, dealer.current_bet);
                }

            } else if (current->name.find("BOT") == std::string::npos) {
                if (current == dealer.big_blind && dealer.current_bet == dealer.big_blind_value) {
                    std::cout << "Enter check, raise, or fold";
                    std::cin >> input_str;
                    if (input_str == "check") {
                        // do nothing
                    }
                    if (input_str == "fold") {
                        current->active_bettor = false;
                    }
                    if (input_str.find("raise") != std::string::npos) {
                    }
                }
            }
        } else {
            continue;
        }

        current = current->next;
    } while (current != dealer.head);

    // dealer.fillBoard();

    // end
    dealer.advanceBlinds();
    if (roundCounter % 5 == 0) {
        dealer.raiseBlinds();
    }
    // }

    return 0;
}