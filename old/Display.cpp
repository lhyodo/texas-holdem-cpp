#include <iostream>

#include "Card.cpp"

// 0 indicates the card is not in play
// 1 indicates the card is in play
// index 0 is first card
// index 51 is last card

class Display {
 private:
 public:
  Display() {
  }
  void displayDeck(Card *deck, int DECK_SIZE) {
    for (int i = 0; i < DECK_SIZE; ++i) {
      std::cout << "Raw value: " << deck[i].getRaw() << "\t" << "Rank: " << deck[i].getRank() << "\t" << "Suit: " << deck[i].getSuit() << std::endl;
    }
  }
  void displayHand(Card* hand, int handSize) {
    for (int i = 0; i < handSize; ++i) {
      Card foo = hand[i];
      std::cout << foo.getCardString() << std::endl;
    }
  }
};
