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
  Player me = Player("You");
  Player frank = Player("BOT Frank");
  Player gary = Player("BOT Gary");
  me.next = &frank;
  frank.next = &gary;
  gary.next = &me;
  dealer.head = &me;  // head of linked list

  // blinds initialization
  int round_counter = 1;
  dealer.small_blind_value = 50;
  dealer.big_blind_value = 100;
  dealer.current_bet = dealer.big_blind_value;
  dealer.small_blind = &frank;
  dealer.big_blind = &gary;

  dealer.
  


  return 0;
}