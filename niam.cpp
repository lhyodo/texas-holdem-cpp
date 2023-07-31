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
    dealer.addPlayer("Player");
    dealer.addPlayer("BOT Frank");
    dealer.addPlayer("BOT Gary");
    dealer.initBlinds();
    dealer.setBlinds(50, 100);

    int roundCounter = 1;
    // while (dealer.getActivePlayerCount() > 1) {
    // dealer.takeBlinds();
    dealer.fillHands();
    dealer.displayHand(dealer.players[0]);

    // pre flop bets
    std::string input_str{};
    Player *current = dealer.start;
    Player *head = dealer.start;
    do {
        if (current->active_bettor == true) {
            if (current->name.find("BOT") != std::string::npos) {
                dealer.takeBet(*current, dealer.current_bet - current->pot);  // call

            } else if (current->name.find("BOT") == std::string::npos) {
                if (current == dealer.big_blind && dealer.current_bet == dealer.big_blind_value) {
                    std::cout << "Enter check, raise, or fold: ";
                    std::getline(std::cin, input_str);
                    if (input_str == "check") {
                        dealer.takeBet(dealer.players[0], dealer.current_bet);
                        std::cout << current->name << " has checked.\n";
                    }
                    if (input_str == "fold") {
                        dealer.takeBet(*current, dealer.big_blind_value);
                        std::cout << current->name << " has folded.\n";
                        current->active_bettor = false;
                    }
                    if (input_str.find("raise") != std::string::npos) {
                        // todo
                        std::string trim = input_str.substr(6);
                        int num = std::stoi(trim);
						dealer.raise(*current, num);
                        dealer.takeBet(*current, dealer.current_bet);
                        head = current;
                    }

                } else if (current == dealer.big_blind && dealer.current_bet != dealer.big_blind_value) {
                    std::cout << "Enter check, raise, or fold: ";
                    std::getline(std::cin, input_str);
                    if (input_str == "call") {
                        dealer.takeBet(dealer.players[0], dealer.current_bet - current->pot);
                        std::cout << current->name << " has checked.\n";
                    }
                    if (input_str == "fold") {
                        dealer.takeBet(*current, dealer.big_blind_value);
                        std::cout << current->name << " has folded.\n";
                        current->active_bettor = false;
                    }
                    if (input_str.find("raise") != std::string::npos) {
                        // todo
                        std::string trim = input_str.substr(6);
                        int num = std::stoi(trim);
						dealer.raise(*current, num);
                        dealer.takeBet(*current, dealer.current_bet);
                        head = current;
                    }

                } else if (current == dealer.small_blind) {
                    std::cout << "Enter call, raise, or fold: ";
                    std::getline(std::cin, input_str);
                    if (input_str == "call") {
                        dealer.takeBet(*current, dealer.current_bet - current->pot);
                        std::cout << current->name << " has called.\n";
                    }
                    if (input_str == "fold") {
                        dealer.takeBet(*current, dealer.small_blind_value);
                        std::cout << current->name << " has folded.\n";
                        current->active_bettor = false;
                    }
                    if (input_str.find("raise") != std::string::npos) {
                        // todo
                        std::string trim = input_str.substr(6);
                        int num = std::stoi(trim);
						dealer.raise(*current, num);
                        dealer.takeBet(*current, dealer.current_bet);
                        head = current;
                    }
                } else if (current != dealer.small_blind && current != dealer.big_blind) {
                    std::cout << "Enter call, raise, or fold: ";
                    std::getline(std::cin, input_str);
                    if (input_str == "call") {
                        std::cout << current->name << " has called.\n";
                        dealer.takeBet(*current, dealer.current_bet - current->pot);
                    }
                    if (input_str == "fold") {
                        std::cout << current->name << " has folded.\n";
                        current->active_bettor = false;
                    }
                    if (input_str.find("raise") != std::string::npos) {
                        // todo
                        std::string trim = input_str.substr(6);
                        int num = std::stoi(trim);
						dealer.raise(*current, num);
                        dealer.takeBet(*current, dealer.current_bet);
                        head = current;
                    }
                }
            }
        } else {
            continue;
        }

        current = current->next;
    } while (current != head);

    if (head != dealer.start) {
        while (current != head) {
            if (current->active_bettor == true) {
                if (current->name.find("BOT") != std::string::npos) {
                    if (current == dealer.big_blind && dealer.current_bet == dealer.big_blind_value) {
                        std::cout << current->name << " has checked.\n";
                        // do nothing
                    } else if (current == dealer.big_blind && dealer.current_bet > dealer.big_blind_value) {
                        std::cout << current->name << " has called.\n";
                        dealer.takeBet(*current, dealer.current_bet - dealer.big_blind_value);
                    } else if (current == dealer.small_blind) {
                        std::cout << current->name << " has called.\n";
                        dealer.takeBet(*current, dealer.current_bet - dealer.small_blind_value);
                    } else if (current != dealer.small_blind && current != dealer.big_blind) {
                        std::cout << current->name << " has called.\n";
                        dealer.takeBet(*current, dealer.current_bet);
                    }
                }
            }
        }
    }

    // dealer.fillBoard();

    // end
    dealer.advanceBlinds();
    if (roundCounter % 5 == 0) {
        dealer.raiseBlinds();
    }
    // }

    return 0;
}