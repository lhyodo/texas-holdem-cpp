#ifndef DEALER
#define DEALER
#include <random>

#include "Card.cpp"
#include "Player.cpp"
#include "QuickSort.cpp"

// Deck is organized from 2 of clubs at index 0 and ace of spades at index 51
// Order of suits is alphabetical. clubs, diamonds, hearts, spades
// Rank of a card is obtained by the formula card_raw/4, as defined in GetRank.cpp
// A "Jack" card has a rank of 9
// A    "2" card has a rank of 0
// An "Ace" card has a rank of 12

// Suit of a card is obtained by the formula card_raw%4, as defined in GetSuit.cpp
// A "Spades" card has a suit of 3
// A  "Clubs" card has a suit of 0

class Dealer {
 private:
 public:
  static const int DECK_SIZE = 52;
  static const int BOARD_SIZE = 5;
  Card deck[DECK_SIZE];
  Card board[BOARD_SIZE];

  Dealer() {
    for (int i = 0; i < DECK_SIZE; ++i) {
      deck[i].setCard(i);
    }
  }

  void displayDeck() {
    for (int i = 0; i < DECK_SIZE; ++i) {
      std::cout << "Raw value: " << deck[i].getRaw() << std::endl;
    }
  }
  void displayHand(Player &player) {
    for (int i = 0; i < player.HAND_SIZE; ++i) {
      Card foo = player.hand[i];
      std::cout << foo.getCardString() << std::endl;
    }
  }
  void fillHand(Player &player) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, DECK_SIZE - 1);
    int arr_counter = 0;
    while (arr_counter < player.HAND_SIZE) {
      int rand_card = dist(rng);
      if (deck[rand_card].getRaw() != -1) {
        player.hand[arr_counter].setCard(rand_card);
        ++arr_counter;
        deck[rand_card] = -1;
      }
    }
  }
  void resetDeck() {
    for (int i = 0; i < DECK_SIZE; ++i) {
      deck[i].setCard(i);
    }
  }
  void fillBoard() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, DECK_SIZE - 1);
    int arr_counter = 0;
    while (arr_counter < BOARD_SIZE) {
      int rand_card = dist(rng);
      if (deck[rand_card].getRaw() != -1) {
        board[arr_counter].setCard(rand_card);
        ++arr_counter;
        deck[rand_card] = -1;
      }
    }
  }
  void displayBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
      std::cout << board[i].getCardString() << std::endl;
    }
  }

  // helper method
  void combineCards(Player &player, Card *combined) {
    int index = 0;
    for (int i = 0; i < player.HAND_SIZE; ++i) {
      combined[index++] = player.hand[i];
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
      combined[index++] = board[i];
    }
    quickSort(combined, 0, player.HAND_SIZE + BOARD_SIZE - 1);
  }

  // A "Jack" card has a rank of 9
  // A    "2" card has a rank of 0
  // An "Ace" card has a rank of 12
  int getHighestRank(Player &player) {
    Card combined[player.HAND_SIZE + BOARD_SIZE];
    combineCards(player, combined);
    quickSort(combined, 0, player.HAND_SIZE + BOARD_SIZE - 1);
    return combined[player.HAND_SIZE + BOARD_SIZE - 1].getRank();
  }

  bool isPair(Player &player) {

    // This function gets the highest pair and stores it in the first 2 slots of top_five_cards
    // The next 3 slots are filled with the highest cards in combined_cards
    // This function does not work if there is a higher combination of cards such as
    // full house, double pair, flush, straight, etc.
    // This function will only take the top pair and store it along with the highest 3 cards

    // Append hand cards array with community cards array for ease of coding
    // In this context combined_cards is hand + community cards
    // Index of 0 and 1 will be from the hand, 2 to 6 will be the board cards

    // ranks_sum = how many cards there are of each rank
    // eg cards of "2 of clubs" "4 of hearts" "4 of spades"
    // ranks_sum = {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    Card combined[player.HAND_SIZE + BOARD_SIZE]{};
    combineCards(player, combined);

    int ranks_sum[13]{};
    for (int i = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
      ++ranks_sum[combined[i].getRank()];
    }

    int pair_rank = -1;
    int num_of_pairs = 0;
    for (int i = 0; i <= 12; ++i) {
      if (ranks_sum[i] == 2) {
        ++num_of_pairs;
        pair_rank = i;
      }
    }
    if (num_of_pairs != 1) {
      return false;
    }

    // Fill first 2 slots of top_five_cards with the pair in raw form
    int top_cards_index = 0;
    for (int i = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
      if (top_cards_index == 2) {
        break;
      }

      if (combined[i].getRank() == pair_rank) {
        player.top_cards[top_cards_index++] = combined[i];
      }
    }

    // Fill last 3 slots of top_five_cards with highest 3 cards excluding the pair
    for (int i = player.HAND_SIZE + BOARD_SIZE - 1; i >= 0; --i) {
      if (top_cards_index == player.TOP_SIZE) {
        break;
      }
      if (player.top_cards[0] == combined[i] || player.top_cards[1] == combined[i]) {
        continue;
      } else {
        player.top_cards[top_cards_index++] = combined[i];
      }
    }
    return true;
  }
};
#endif