#include <iostream>
#include <string>
#include <vector>

#include "Card.cpp"
#include "Dealer.cpp"
#include "Player.cpp"
#include "QuickSort.cpp"

int main() {
    Dealer dealer{};
    dealer.addPlayer("Me");
    dealer.addPlayer("BOT");
    dealer.initBlinds();
    dealer.setBlinds(50, 100);

    dealer.players[0].hand[0] = 11;
    dealer.players[0].hand[1] = 47;
    dealer.players[1].hand[0] = 13;
    dealer.players[1].hand[1] = 19;
    dealer.board[0] = 33;
    dealer.board[1] = 8;
    dealer.board[2] = 35;
    dealer.board[3] = 51;
    dealer.board[4] = 14;

    dealer.displayHand(dealer.players[0]);
    dealer.displayBoard();

    dealer.displayHand(dealer.players[1]);

    bool pair_flag = dealer.isPair(dealer.players[0]);
    bool dpair_flag = dealer.isDoublePair(dealer.players[0]);
    bool tkind_flag = dealer.isThreeKind(dealer.players[0]);
    bool straight_flag = dealer.isStraight(dealer.players[0]);
    bool flush_flag = dealer.isFlush(dealer.players[0]);
    bool fhouse_flag = dealer.isFullHouse(dealer.players[0]);
    bool fkind_flag = dealer.isFourKind(dealer.players[0]);
    bool sflush_flag = dealer.isStraightFlush(dealer.players[0]);
    std::cout << "pair_flag flag: " << pair_flag << std::endl;
    std::cout << "dpair_flag flag: " << dpair_flag << std::endl;
    std::cout << "tkind_flag flag: " << tkind_flag << std::endl;
    std::cout << "fkind_flag flag: " << fkind_flag << std::endl;
    std::cout << "flush_flag flag: " << flush_flag << std::endl;
    std::cout << "fhouse_flag flag: " << fhouse_flag << std::endl;
    std::cout << "straight flag: " << straight_flag << std::endl;
    std::cout << "sflush_flag flag: " << sflush_flag << std::endl;
    std::cout << "==========\n";
    std::cout << "Primary Cards: \n";
    for (int i = 0; i < 5; ++i) {
        std::string foo = dealer.players[0].primary_cards[i].getCardString();
        std::cout << foo << std::endl;
    }
    std::cout << "==========\n";
    std::cout << "Secondary Cards: \n";
    for (int i = 0; i < 5; ++i) {
        std::string foo = dealer.players[0].secondary_cards[i].getCardString();
        std::cout << foo << std::endl;
    }
    std::cout << "\n==================================================\n\n";
    dealer.assignPoints();
    std::cout << "Your points:  " << dealer.players[0].hand_points << '\n';
    std::cout << "BOT's points: " << dealer.players[1].hand_points << '\n';

    if (dealer.players[0].hand_points == dealer.players[1].hand_points) {
        bool isdp = dealer.isDoublePair(dealer.players[0]);
        if (isdp == true) {
            if (dealer.players[0].primary_cards[3].getRank() >= dealer.players[1].primary_cards[3].getRank()) {
                std::cout << "You win!\n";
            }
        } else {
            std::cout << "You win!\n";
        }
    }
    if (dealer.players[1].hand_points == dealer.players[0].hand_points) {
        bool isdp = dealer.isDoublePair(dealer.players[0]);
        if (isdp == true) {
            if (dealer.players[1].primary_cards[3].getRank() >= dealer.players[0].primary_cards[3].getRank()) {
                std::cout << dealer.players[1].name << " wins.\n";
            }
        } else {
            std::cout << dealer.players[1].name << " wins.\n";
        }
    }

    return 0;
}
