
#ifndef PLAYER
#define PLAYER
#include "Card.cpp"
#include <string>

class Player {
 private:
 public:
  static const int TOP_SIZE = 5;
  static const int HAND_SIZE = 2;
  std::string name{};
  int chips = 1000;
  int hand_points{};
  int pot{};
  bool active_bettor = true;
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
  bool operator==(const Player &rhs) const noexcept {
    if (name == rhs.name) {
      return true;
    }
    return false;
  }

  bool equalHand(const Player &rhs) {
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