
#ifndef PLAYER
#define PLAYER
#include "Card.cpp"

class Player {
 private:
 public:
  static const int TOP_SIZE = 5;
  static const int HAND_SIZE = 2;
  int chips = 500;
  int hand_points{};
  Card primary_cards[TOP_SIZE]{};
  Card secondary_cards[TOP_SIZE]{};
  Card hand[HAND_SIZE]{};
  Player() {
    for (int i = 0; i < TOP_SIZE; ++i) {
      primary_cards[i].setCard(-1);
      secondary_cards[i].setCard(-1);
    }
    for (int i = 0; i < HAND_SIZE; ++i) {
      hand[i].setCard(-1);
    }
  }
  bool equalHand(Player &rhs) {
    for (int i = 0; i < TOP_SIZE; ++i) {
      if (primary_cards[i] != rhs.primary_cards[i]) {
        return false;
      }
      if (secondary_cards[i] != rhs.secondary_cards[i]) {
        return false;
      }
    }
    return true;
  }
};
#endif