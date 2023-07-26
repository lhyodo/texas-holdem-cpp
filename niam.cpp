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
    dealer.addPlayer("Frank");
    dealer.addPlayer("Gary");
    dealer.initBlinds();
    dealer.setBlinds(50, 100);

    



    // while (dealer.getActivePlayerCount() > 1) {
      dealer.takeBlinds();
      dealer.fillHands();
      dealer.displayHand(dealer.players[0]);
    // }

        return 0;
}