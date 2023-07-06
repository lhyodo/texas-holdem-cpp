#include <random>

#include "Card.cpp"
#include "quickSort.cpp"

class Dealer {
 private:
  static const int DECK_SIZE = 52;
  static const int BOARD_SIZE = 5;
  static const int HAND_SIZE = 2;
  void combineCards(Card *your_hand, Card *combined) {
    int index = 0;
    for (int i = 0; i < HAND_SIZE; ++i) {
      combined[index++] = your_hand[i];
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
      combined[index++] = board[i];
    }
    quickSort(combined, 0, HAND_SIZE + BOARD_SIZE - 1);
  }

 public:
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
  void displayHand(Card *hand) {
    for (int i = 0; i < HAND_SIZE; ++i) {
      Card foo = hand[i];
      std::cout << foo.getCardString() << std::endl;
    }
  }
  void fillHand(Card *hand) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, 51);
    int arr_counter = 0;
    while (arr_counter < HAND_SIZE) {
      int rand_card = dist(rng);
      if (deck[rand_card].getRaw() != -1) {
        hand[arr_counter].setCard(rand_card);
        ++arr_counter;
        deck[rand_card] = -1;
      }
    }
  }
  void fillBoard() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, 51);
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

  int getHighestRank(Card *hand) {
    Card combined[HAND_SIZE + BOARD_SIZE];
    combineCards(hand, combined);
    quickSort(combined, 0, HAND_SIZE + BOARD_SIZE - 1);
    return combined[HAND_SIZE + BOARD_SIZE - 1].getRank();
  }

  bool isPair(Card *hand, int handSize, Card *top_five_cards) {
    // ===================== NOTE =====================
    // Deck is organized from 2 of clubs at index 0 and ace of spades at index 51
    // Order of suits is alphabetical. clubs, diamonds, hearts, spades
    // Rank of a card is obtained by the formula card_raw/4, as defined in GetRank.cpp
    // A "Jack" card has a rank of 9
    // A    "2" card has a rank of 0
    // An "Ace" card has a rank of 12

    // Suit of a card is obtained by the formula card_raw%4, as defined in GetSuit.cpp
    // A "Spades" card has a suit of 3
    // A  "Clubs" card has a suit of 0

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
    Card combined[7]{};
    combineCards(hand, board, 2, 5, combined);

    int ranks_sum[13]{};
    for (int i = 0; i < 7; ++i) {
      Card card = combined[i];
      int rank = card.getRank();
      ++ranks_sum[rank];
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
    for (int j = 6; j >= 0; --j) {
      if (top_cards_index == 2) {
        break;
      }

      if (combined[j].getRank() == pair_rank) {
        top_five_cards[top_cards_index++] = combined[j];
      }
    }

    // Fill last 3 slots of top_five_cards with highest 3 cards excluding the pair
    for (int i = handSize - 1; i >= 0; --i) {
      if (top_cards_index == 5) {
        break;
      }
      if (top_five_cards[0] == combined[i] || top_five_cards[1] == combined[i]) {
        continue;
      } else {
        top_five_cards[top_cards_index++] = combined[i];
      }
    }

    return true;
  }
};
