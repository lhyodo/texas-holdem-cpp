
#ifndef PLAYER
#define PLAYER
#include "Card.cpp"

class Player {
 private:
 public:
  static const int TOP_SIZE = 5;
  static const int HAND_SIZE = 2;
  int chips = 500;
  Card top_cards[TOP_SIZE]{};
  Card hand[HAND_SIZE]{};
  Player() {
    for (int i = 0; i < TOP_SIZE; ++i) {
      top_cards[i].setCard(-1);
    }
    for (int i = 0; i < HAND_SIZE; ++i) {
      hand[i].setCard(-1);
    }
  }
};
#endif