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
    dealer.fillHands();
    dealer.displayHand(dealer.players[0]);

    // pre flop bets
    std::string input_str{};
    Player *current = dealer.start;
    Player *head = dealer.start;
    do {
        if (current->active_bettor == true) {
            if (current->name.find("BOT") != std::string::npos) {
                dealer.call(*current);  // BOT will always call

            } else if (current->name.find("BOT") == std::string::npos) {
                if (current == dealer.big_blind && dealer.current_bet == dealer.big_blind_value) {
                    std::cout << "Enter check, raise, or fold: ";
                    std::getline(std::cin, input_str);
                    if (input_str == "check") {
                        dealer.check(*current);
                        std::cout << current->name << " has checked.\n";
                    }
                    if (input_str == "fold") {
                        dealer.fold(*current);
                        std::cout << current->name << " has folded.\n";
                    }
                    if (input_str.find("raise") != std::string::npos) {
                        std::string trim = input_str.substr(6);
                        int num = std::stoi(trim);
                        dealer.raise(*current, num);
                        head = current;
                    }

                } else if (current == dealer.big_blind && dealer.current_bet != dealer.big_blind_value) {
                    std::cout << "Enter check, raise, or fold: ";
                    std::getline(std::cin, input_str);
                    if (input_str == "call") {
                        dealer.call(*current);
                        std::cout << current->name << " has checked.\n";
                    }
                    if (input_str == "fold") {
                        dealer.fold(*current);
                        std::cout << current->name << " has folded.\n";
                    }
                    if (input_str.find("raise") != std::string::npos) {
                        // todo
                        std::string trim = input_str.substr(6);
                        int num = std::stoi(trim);
                        dealer.raise(*current, num);
                        head = current;
                    }

                } else if (current == dealer.small_blind) {
                    std::cout << "Enter call, raise, or fold: ";
                    std::getline(std::cin, input_str);
                    if (input_str == "call") {
                        dealer.call(*current);
                        std::cout << current->name << " has called.\n";
                    }
                    if (input_str == "fold") {
                        dealer.fold(*current);
                        std::cout << current->name << " has folded.\n";
                    }
                    if (input_str.find("raise") != std::string::npos) {
                        // todo
                        std::string trim = input_str.substr(6);
                        int num = std::stoi(trim);
                        dealer.raise(*current, num);
                        head = current;
                    }
                } else if (current != dealer.small_blind && current != dealer.big_blind) {
                    std::cout << "Enter call, raise, or fold: ";
                    std::getline(std::cin, input_str);
                    if (input_str == "call") {
                        std::cout << current->name << " has called.\n";
                        dealer.call(*current);
                    }
                    if (input_str == "fold") {
                        dealer.fold(*current);
                        std::cout << current->name << " has folded.\n";
                    }
                    if (input_str.find("raise") != std::string::npos) {
                        // todo
                        std::string trim = input_str.substr(6);
                        int num = std::stoi(trim);
                        dealer.raise(*current, num);
                        head = current;
                    }
                }
            }
        } else {
            continue;
        }

        current = current->next;
    } while (current != head);

    dealer.fillBoard();
    dealer.displayFlop();
    // post flop bets
    current = dealer.start;
    head = dealer.start;
    do {
        if (current->active_bettor == true) {
            if (current->name.find("BOT") != std::string::npos) {
                dealer.call(*current);  // BOT will always call
            }

            else if (current->name.find("BOT") == std::string::npos) {
                std::cout << "Enter check, raise, or fold: ";
                std::getline(std::cin, input_str);
                if (input_str == "check") {
                    dealer.check(*current);
                    std::cout << current->name << " has checked.\n";
                }
                if (input_str == "fold") {
                    current->active_bettor = false;
                    std::cout << current->name << " has folded.\n";
                }
                if (input_str.find("raise") != std::string::npos) {
                    std::string trim = input_str.substr(6);
                    int num = std::stoi(trim);
                    dealer.raise(*current, num);
                    head = current;
                }
            }
        } else {
            continue;
        }
        current = current->next;
    } while (current != head);

    dealer.displayTurn();
    // post turn bets
    current = dealer.start;
    head = dealer.start;
    do {
        if (current->active_bettor == true) {
            if (current->name.find("BOT") != std::string::npos) {
                dealer.call(*current);  // BOT will always call
            }

            else if (current->name.find("BOT") == std::string::npos) {
                std::cout << "Enter check, raise, or fold: ";
                std::getline(std::cin, input_str);
                if (input_str == "check") {
                    dealer.check(*current);
                    std::cout << current->name << " has checked.\n";
                }
                if (input_str == "fold") {
                    current->active_bettor = false;
                    std::cout << current->name << " has folded.\n";
                }
                if (input_str.find("raise") != std::string::npos) {
                    std::string trim = input_str.substr(6);
                    int num = std::stoi(trim);
                    dealer.raise(*current, num);
                    head = current;
                }
            }
        } else {
            continue;
        }
        current = current->next;
    } while (current != head);

    dealer.displayRiver();
    // post river bets (final bets)
    current = dealer.start;
    head = dealer.start;
    do {
        if (current->active_bettor == true) {
            if (current->name.find("BOT") != std::string::npos) {
                dealer.call(*current);  // BOT will always call
            }

            else if (current->name.find("BOT") == std::string::npos) {
                std::cout << "Enter check, raise, or fold: ";
                std::getline(std::cin, input_str);
                if (input_str == "check") {
                    dealer.check(*current);
                    std::cout << current->name << " has checked.\n";
                }
                if (input_str == "fold") {
                    current->active_bettor = false;
                    std::cout << current->name << " has folded.\n";
                }
                if (input_str.find("raise") != std::string::npos) {
                    std::string trim = input_str.substr(6);
                    int num = std::stoi(trim);
                    dealer.raise(*current, num);
                    head = current;
                }
            }
        } else {
            continue;
        }
        current = current->next;
    } while (current != head);

    // calculate and decide winner

    // end
    dealer.advanceBlinds();
    if (roundCounter % 5 == 0) {
        dealer.raiseBlinds();
    }
    // }

    return 0;
}