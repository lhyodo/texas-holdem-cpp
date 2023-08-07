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

    dealer.players[0].hand[0] = 14;
    dealer.players[0].hand[1] = 13;
    dealer.players[1].hand[0] = 22;
    dealer.players[1].hand[1] = 49;
    dealer.board[0] = 6;
    dealer.board[1] = 12;
    dealer.board[2] = 22;
    dealer.board[3] = 21;
    dealer.board[4] = 20;

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
    dealer.assignPoints(dealer.players[0]);
    std::cout << "Your points:  " << dealer.players[0].hand_points << '\n';

    dealer.assignPoints(dealer.players[1]);
    std::cout << "BOT's points: " << dealer.players[1].hand_points << '\n';

    return 0;
}
