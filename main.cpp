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
    while (dealer.getActivePlayerCount() > 1) {
        std::cout << "------------------------------\n";
        std::cout << "Big blind: " << dealer.big_blind->name << std::endl;
        std::cout << "Small blind: " << dealer.small_blind->name << std::endl;
        std::cout << "Starter: " << dealer.start->name << std::endl;
        std::cout << "------------------------------\n";
        dealer.takeBlinds();
        dealer.fillHands();
        dealer.fillBoard();
        // debug
        // dealer.players[0].hand[0] = 45;
        // dealer.players[0].hand[1] = 21;
        // dealer.players[1].hand[0] = 40;
        // dealer.players[1].hand[1] = 20;
        // dealer.board[0] = 2;
        // dealer.board[1] = 10;
        // dealer.board[2] = 39;
        // dealer.board[3] = 51;
        // dealer.board[4] = 12;
        // end debug
        dealer.displayHand(dealer.players[0]);

        // pre flop bets
        std::string input_str{};
        Player *current = dealer.start;
        Player *head = dealer.start;
        do {
            if (current->active_bettor == true) {
                if (current->name.find("BOT") != std::string::npos) {
                    if (current == dealer.big_blind && dealer.bet_amt == dealer.big_blind_value) {
                        dealer.check(*current);
                        std::cout << current->name << " has checked.\n";
                    } else {
                        dealer.call(*current);  // BOT will always call
                        std::cout << current->name << " has called.\n";
                    }

                } else if (current->name.find("BOT") == std::string::npos) {
                    if (current == dealer.big_blind && dealer.bet_amt == dealer.big_blind_value) {
                        std::cout << "Enter check, raise #, or fold: ";
                        std::getline(std::cin, input_str);
                        while (input_str != "check" && input_str.find("raise") == std::string::npos && input_str != "fold") {
                            std::cout << "Invalid input.\n";
                            std::cout << "Enter check, raise #, or fold: ";
                            std::getline(std::cin, input_str);
                        }
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

                    } else if (current == dealer.big_blind && dealer.bet_amt != dealer.big_blind_value) {
                        std::cout << "Enter call, raise #, or fold: ";
                        std::getline(std::cin, input_str);
                        while (input_str != "call" && input_str.find("raise") == std::string::npos && input_str != "fold") {
                            std::cout << "Invalid input.\n";
                            std::cout << "Enter check, raise #, or fold: ";
                            std::getline(std::cin, input_str);
                        }
                        if (input_str == "call") {
                            dealer.call(*current);
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

                    } else if (current == dealer.small_blind) {
                        std::cout << "Enter call, raise #, or fold: ";
                        std::getline(std::cin, input_str);
                        while (input_str != "call" && input_str.find("raise") == std::string::npos && input_str != "fold") {
                            std::cout << "Invalid input.\n";
                            std::cout << "Enter call, raise #, or fold: ";
                            std::getline(std::cin, input_str);
                        }
                        if (input_str == "call") {
                            dealer.call(*current);
                            std::cout << current->name << " has called.\n";
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
                    } else if (current != dealer.small_blind && current != dealer.big_blind) {
                        std::cout << "Enter call, raise #, or fold: ";
                        std::getline(std::cin, input_str);
                        while (input_str != "call" && input_str.find("raise") == std::string::npos && input_str != "fold") {
                            std::cout << "Invalid input.\n";
                            std::cout << "Enter call, raise #, or fold: ";
                            std::getline(std::cin, input_str);
                        }
                        if (input_str == "call") {
                            std::cout << current->name << " has called.\n";
                            dealer.call(*current);
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
                    }
                }
            } else {
                current = current->next;
                continue;
            }

            current = current->next;
        } while (current != head);

        
        dealer.displayFlop();
        // post flop bets
        current = dealer.start;
        head = dealer.start;
        do {
            if (current->active_bettor == true) {
                if (current->name.find("BOT") != std::string::npos) {
                    if (dealer.bet_amt == current->pot) {
                        dealer.check(*current);
                        std::cout << current->name << " has checked.\n";
                    }
                    if (dealer.bet_amt != current->pot) {
                        dealer.call(*current);  // BOT will always call
                        std::cout << current->name << " has called.\n";
                    }
                }

                else if (current->name.find("BOT") == std::string::npos) {
                    std::cout << "Enter check, raise #, or fold: ";
                    std::getline(std::cin, input_str);
                    while (input_str != "check" && input_str.find("raise") == std::string::npos && input_str != "fold") {
                        std::cout << "Invalid input.\n";
                        std::cout << "Enter check, raise #, or fold: ";
                        std::getline(std::cin, input_str);
                    }
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
                }
            } else {
                current = current->next;
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
                    if (dealer.bet_amt == current->pot) {
                        dealer.check(*current);
                        std::cout << current->name << " has checked.\n";
                    }
                    if (dealer.bet_amt != current->pot) {
                        dealer.call(*current);  // BOT will always call
                        std::cout << current->name << " has called.\n";
                    }
                }

                else if (current->name.find("BOT") == std::string::npos) {
                    std::cout << "Enter check, raise #, or fold: ";
                    std::getline(std::cin, input_str);
                    while (input_str != "check" && input_str.find("raise") == std::string::npos && input_str != "fold") {
                        std::cout << "Invalid input.\n";
                        std::cout << "Enter check, raise #, or fold: ";
                        std::getline(std::cin, input_str);
                    }
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
                }
            } else {
                current = current->next;
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
                    if (dealer.bet_amt == current->pot) {
                        dealer.check(*current);
                        std::cout << current->name << " has checked.\n";
                    }
                    if (dealer.bet_amt != current->pot) {
                        dealer.call(*current);  // BOT will always call
                        std::cout << current->name << " has called.\n";
                    }
                }

                else if (current->name.find("BOT") == std::string::npos) {
                    std::cout << "Enter check, raise #, or fold: ";
                    std::getline(std::cin, input_str);
                    while (input_str != "check" && input_str.find("raise") == std::string::npos && input_str != "fold") {
                        std::cout << "Invalid input.\n";
                        std::cout << "Enter check, raise #, or fold: ";
                        std::getline(std::cin, input_str);
                    }
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
                }
            } else {
                current = current->next;
                continue;
            }
            current = current->next;
        } while (current != head);

        // show hands
        std::cout << "Showing cards: \n";
        dealer.displayHand(dealer.players[0]);
        dealer.displayHand(dealer.players[1]);
        dealer.displayHand(dealer.players[2]);

        // show board again
        dealer.displayBoard();

        // calculate and decide winner
        dealer.assignPoints();
        for (auto i = dealer.players.begin(); i != dealer.players.end(); ++i) {
            std::cout << (*i).name << "'s hand points: " << (*i).hand_points << std::endl;
        }

        std::string win_msg{};

        if (dealer.players[0].hand_points > dealer.players[1].hand_points && dealer.players[0].hand_points > dealer.players[2].hand_points) {
            win_msg = "You win!\n";
            int all_pot = 0;
            for (auto i = dealer.players.begin(); i != dealer.players.end(); ++i) {
                dealer.players[0].chips += i->pot;
            }
        } else if (dealer.players[1].hand_points > dealer.players[0].hand_points && dealer.players[1].hand_points > dealer.players[2].hand_points) {
            win_msg = dealer.players[1].name + " wins.\n";
            int all_pot = 0;
            for (auto i = dealer.players.begin(); i != dealer.players.end(); ++i) {
                dealer.players[1].chips += i->pot;
            }
        } else if (dealer.players[2].hand_points > dealer.players[0].hand_points && dealer.players[2].hand_points > dealer.players[1].hand_points) {
            win_msg = dealer.players[2].name + " wins.\n";
            int all_pot = 0;
            for (auto i = dealer.players.begin(); i != dealer.players.end(); ++i) {
                dealer.players[2].chips += i->pot;
            }
        } else if (dealer.players[0].hand_points == dealer.players[1].hand_points && dealer.players[0].hand_points == dealer.players[2].hand_points) {
            win_msg = "You win!\n";
            win_msg += dealer.players[1].name + " wins.\n";
            win_msg += dealer.players[2].name + " wins.\n";
        } else if (dealer.players[0].hand_points == dealer.players[1].hand_points) {
            win_msg = "You win!\n";
            win_msg += dealer.players[1].name + " wins.\n";
        } else if (dealer.players[0].hand_points == dealer.players[2].hand_points) {
            win_msg = "You win!\n";
            win_msg += dealer.players[2].name + " wins.\n";
        } else if (dealer.players[1].hand_points == dealer.players[2].hand_points) {
            win_msg = dealer.players[1].name + " wins.\n";
            win_msg += dealer.players[2].name + " wins.\n";
        }
        std::cout << win_msg;

        for (auto i = dealer.players.begin(); i != dealer.players.end(); ++i) {
            if (i->name == "Player") {
                std::cout << "Your chips: " << i->chips << std::endl;
            } else {
                std::cout << i->name << "'s chips: " << i->chips << std::endl;
            }
        }
        std::cout << "Enter \".\" to continue: ";
        std::getline(std::cin, input_str);
        while (input_str != ".") {
            std::getline(std::cin, input_str);
        }

        // if 0 chips, knocked_out = true
        for (auto i = dealer.players.begin(); i != dealer.players.end(); ++i) {
            if (i->chips <= 0) {
                i->knocked_out = true;
            }
        }

        // end
        dealer.roundReset();
        dealer.advanceBlinds();
        ++roundCounter;
        if (roundCounter % 5 == 0) {
            dealer.raiseBlinds();
        }
    }

    return 0;
}