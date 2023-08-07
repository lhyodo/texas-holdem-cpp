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

// Players are a circular linked list, with a "head" to indicate the starting player

class Dealer {
   private:
   public:
    static const int DECK_SIZE = 52;
    static const int BOARD_SIZE = 5;
    static const int HAND_SIZE = 2;
    static const int TOP_SIZE = 5;
    Card deck[DECK_SIZE];
    Card board[BOARD_SIZE];
    int small_blind_value = 50;
    int big_blind_value = 2 * small_blind_value;
    int bet_amt = big_blind_value;
    Player *start{};  // the player that bets first
    Player *small_blind{};
    Player *big_blind{};
    std::vector<Player> players{};

    Dealer() {
        for (int i = 0; i < DECK_SIZE; ++i) {
            deck[i].setCard(i);
        }
    }

    void addPlayer(std::string name) {
        if (players.size() == 0) {
            players.push_back(Player(name));
        } else if (players.size() == 1) {
            players.push_back(Player(name));
            players[0].next = &players[1];
            players[1].next = &players[0];
        } else if (players.size() == 2) {
            players.push_back(Player(name));
            players[0].next = &players[1];
            players[1].next = &players[2];
            players[2].next = &players[0];
        } else if (players.size() == 3) {
            players.push_back(Player(name));
            players[0].next = &players[1];
            players[1].next = &players[2];
            players[2].next = &players[3];
            players[3].next = &players[0];
        } else {
            std::cout << "Max amount of players (4)\n";
        }
    }

    int getActivePlayerCount() {
        int n = 0;
        for (int i = 0; i < players.size(); ++i) {
            if (players[i].knocked_out == false) {
                ++n;
            }
        }
        return n;
    }

    void initBlinds() {
        if (players.size() <= 1) {
            std::cout << "setBlinds error\n";
        }
        if (players.size() == 2) {
            small_blind = &players[0];
            big_blind = &players[1];
            start = &players[0];
        }
        if (players.size() >= 3) {
            small_blind = &players[0];
            big_blind = &players[1];
            start = &players[2];
        }
    }

    void advanceBlinds() {
        small_blind = small_blind->next;
        big_blind = big_blind->next;
        start = start->next;
    }

    void raiseBlinds() {
        small_blind_value *= 2;
        big_blind_value *= 2;
    }

    void activeReset() {
        for (auto i = players.begin(); i != players.end(); ++i) {
            i->active_bettor = true;
        }
    }

    // helper function
    void takeBet(Player &player, int val) {
        if (player.chips <= val) {
            player.pot += player.chips;
            player.chips = 0;
            player.all_in = true;
            std::cout << "Player " << player.name << " has 0 chips and is all in!\n";
        }
        if (player.chips > val) {
            player.pot += val;
            player.chips -= val;
        }
    }

    void check(Player &player) {
        takeBet(player, bet_amt - player.pot);
    }

    void call(Player &player) {
        takeBet(player, bet_amt - player.pot);
    }

    // foldStart only used at pre flop bets
    // fold otherwise is just player.active_bettor
    void foldStart(Player &player) {
        if (player == *big_blind) {
            takeBet(player, big_blind_value);
        }
        if (player == *small_blind) {
            takeBet(player, small_blind_value);
        }
        player.active_bettor = false;
    }

    void fold(Player &player) {
        player.active_bettor = false;
    }

    void raise(Player &player, int val) {
        bet_amt += val;
        takeBet(player, bet_amt - player.pot);
    }

    void setBlinds(int small, int big) {
        small_blind_value = small;
        big_blind_value = big;
    }

    // void setCurrentBet(int n) {
    //     bet_amt = n;
    // }

    // void addCurrentBet(int n) {
    //     bet_amt += n;
    // }

    void displayDeck() {
        for (int i = 0; i < DECK_SIZE; ++i) {
            std::cout << "Raw value: " << deck[i].getRaw() << std::endl;
        }
    }

    void displayHand(Player &player) {
        std::cout << "------------------------------\n";
        std::cout << "Your Hand:\n";
        for (int i = 0; i < player.HAND_SIZE; ++i) {
            Card foo = player.hand[i];
            std::cout << foo.getCardString() << std::endl;
        }
        std::cout << "------------------------------\n";
    }

    void fillHands() {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<> dist(0, DECK_SIZE - 1);

        for (auto it = players.begin(); it != players.end(); ++it) {
            int foo = 0;
            while (foo < HAND_SIZE) {
                int rand_card = dist(rng);
                if (deck[rand_card].getRaw() != -1) {
                    it->hand[foo].setCard(rand_card);
                    ++foo;
                    deck[rand_card] = -1;
                }
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

    // debug function
    void displayBoard() {
        std::cout << "==============================\n";
        std::cout << "The Board: \n";
        for (int i = 0; i < BOARD_SIZE; ++i) {
            std::cout << board[i].getCardString() << std::endl;
        }
        std::cout << "==============================\n";
    }

    void displayFlop() {
        std::cout << "==============================\n";
        std::cout << "The Flop: \n";
        for (int i = 0; i < 3; ++i) {
            std::cout << board[i].getCardString() << std::endl;
        }
        std::cout << "==============================\n";
    }

    void displayTurn() {
        std::cout << "==============================\n";
        std::cout << "The Turn: \n";
        std::cout << board[3].getCardString() << std::endl;
        std::cout << "==============================\n";
    }

    void displayRiver() {
        std::cout << "==============================\n";
        std::cout << "The River: \n";
        std::cout << board[4].getCardString() << std::endl;
        std::cout << "==============================\n";
    }

    void roundReset() {
        for (int i = 0; i < players.size(); ++i) {
            players[i].active_bettor = true;
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

    bool isStraightFlush(Player &player) {
        // this function is derived from isFlush
        Card combined[player.HAND_SIZE + BOARD_SIZE]{};
        combineCards(player, combined);
        int suits_sum[4]{};
        for (int i = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            ++suits_sum[combined[i].getSuit()];
        }
        bool flush_flag = false;
        int flush_suit = -1;
        for (int i = 0; i < 4; ++i) {
            if (suits_sum[i] >= TOP_SIZE) {
                flush_flag = true;
                flush_suit = i;
            }
        }
        if (flush_flag == false) {
            return false;
        }
        Card same_suit[HAND_SIZE + BOARD_SIZE]{};
        for (int i = HAND_SIZE + BOARD_SIZE - 1, j = 0; i >= 0; --i) {
            if (combined[i].getSuit() == flush_suit) {
                same_suit[j++] = combined[i];
            }
        }
        Card straight_flush_cards[TOP_SIZE]{};
        bool isStraightHelper_flag = isStraightHelper(same_suit, straight_flush_cards);
        if (isStraightHelper_flag == false) {
            return false;
        }
        for (int i = 0; i < TOP_SIZE; ++i) {
            player.primary_cards[i] = straight_flush_cards[i];
        }

        return true;
    }

    bool isStraightHelper(Card cards[HAND_SIZE + BOARD_SIZE], Card straight_flush_cards[TOP_SIZE]) {
        int ranks_sum[13]{};
        for (int i = 0; i < HAND_SIZE + BOARD_SIZE; ++i) {
            ++ranks_sum[cards[i].getRank()];
        }
        int straight_flag = false;
        int highest_rank_in_straight = -1;
        for (int i = 12; i >= 4; --i) {
            if (ranks_sum[i] > 0 && ranks_sum[i - 1] > 0 && ranks_sum[i - 2] > 0 && ranks_sum[i - 3] > 0 && ranks_sum[i - 4] > 0) {
                straight_flag = true;
                highest_rank_in_straight = i;
                break;
            }
        }
        if (straight_flag == false) {
            return false;
        }
        Card flush_cards[7]{};
        for (int i = HAND_SIZE + BOARD_SIZE - 1; i >= 0; --i) {
            for (int j = 0; j < TOP_SIZE; ++j) {
                if (cards[i].getRank() == highest_rank_in_straight - j) {
                    flush_cards[j] = cards[i];
                }
            }
        }
        for (int i = 0; i < TOP_SIZE; ++i) {
            straight_flush_cards[i] = flush_cards[i];
        }
        return true;
    }

    bool isStraight(Player &player) {
        Card combined[player.HAND_SIZE + BOARD_SIZE]{};
        combineCards(player, combined);
        int ranks_sum[13]{};
        for (int i = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            ++ranks_sum[combined[i].getRank()];
        }
        int straight_flag = false;
        int highest_rank_in_straight = -1;
        for (int i = 12; i >= 4; --i) {
            if (ranks_sum[i] > 0 && ranks_sum[i - 1] > 0 && ranks_sum[i - 2] > 0 && ranks_sum[i - 3] > 0 && ranks_sum[i - 4] > 0) {
                straight_flag = true;
                highest_rank_in_straight = i;
                break;
            }
        }
        if (straight_flag == false) {
            return false;
        }
        bool flush_flag = isFlush(player);
        if (flush_flag == true) {
            return false;
        }
        bool is_straight_flush_flag = isStraightFlush(player);
        if (is_straight_flush_flag == true) {
            return false;
        }
        for (int i = HAND_SIZE + BOARD_SIZE - 1; i >= 0; --i) {
            for (int j = 0; j < TOP_SIZE; ++j) {
                if (combined[i].getRank() == highest_rank_in_straight - j) {
                    player.primary_cards[j] = combined[i];
                }
            }
        }

        return true;
    }

    bool isFlush(Player &player) {
        Card combined[player.HAND_SIZE + BOARD_SIZE]{};
        combineCards(player, combined);
        int suits_sum[4]{};
        for (int i = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            ++suits_sum[combined[i].getSuit()];
        }
        bool flush_flag = false;
        int flush_suit = -1;
        for (int i = 0; i < 4; ++i) {
            if (suits_sum[i] >= TOP_SIZE) {
                flush_flag = true;
                flush_suit = i;
            }
        }
        if (flush_flag == false) {
            return false;
        }
        bool straight_flush_flag = isStraightFlush(player);
        if (straight_flush_flag == true) {
            return false;
        }

        for (int i = HAND_SIZE + BOARD_SIZE - 1, primary_cards_index = 0; i >= 0; --i) {
            if (primary_cards_index == TOP_SIZE) {
                break;
            }
            if (combined[i].getSuit() == flush_suit) {
                player.primary_cards[primary_cards_index++] = combined[i];
            }
        }
        return true;
    }

    bool isFourKind(Player &player) {
        // this function is derived from isThreeKind
        Card combined[player.HAND_SIZE + BOARD_SIZE]{};
        combineCards(player, combined);

        int ranks_sum[13]{};
        for (int i = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            ++ranks_sum[combined[i].getRank()];
        }

        int four_kind_rank = -1;
        int num_of_four_kinds = 0;
        for (int i = 0; i <= 12; ++i) {
            if (ranks_sum[i] == 4) {
                ++num_of_four_kinds;
                four_kind_rank = i;
            }
        }
        if (num_of_four_kinds != 1) {
            return false;
        }

        // Fill first 4 slots of primary_cards with the four kind in raw form
        for (int i = 0, primary_cards_index = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            if (primary_cards_index == 4) {
                break;
            }

            if (combined[i].getRank() == four_kind_rank) {
                player.primary_cards[primary_cards_index++] = combined[i];
            }
        }

        // Fill 1 slots of secondary_cards with highest 1 cards excluding the four kind
        for (int i = player.HAND_SIZE + BOARD_SIZE - 1, secondary_cards_index = 0; i >= 0; --i) {
            if (secondary_cards_index == 1) {
                break;
            }
            if (player.primary_cards[0] == combined[i] || player.primary_cards[1] == combined[i] || player.primary_cards[2] == combined[i] || player.primary_cards[3] == combined[i]) {
                continue;
            } else {
                player.secondary_cards[secondary_cards_index++] = combined[i];
            }
        }
        return true;
    }

    bool isFullHouse(Player &player) {
        // this function is derived from isThreeKind
        Card combined[player.HAND_SIZE + BOARD_SIZE]{};
        combineCards(player, combined);

        int ranks_sum[13]{};
        for (int i = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            ++ranks_sum[combined[i].getRank()];
        }

        int num_of_three_kinds = 0;
        int three_kind_rank = -1;
        for (int i = 0; i <= 12; ++i) {
            if (ranks_sum[i] == 3) {
                ++num_of_three_kinds;
                three_kind_rank = i;
            }
        }
        int num_of_pairs = 0;
        int pair_rank = -1;
        for (int i = 0; i <= 12; ++i) {
            if (ranks_sum[i] == 2) {
                ++num_of_pairs;
                pair_rank = i;
            }
        }
        int num_of_four_kinds = 0;
        for (int i = 0; i <= 12; ++i) {
            if (ranks_sum[i] == 4) {
                ++num_of_four_kinds;
            }
        }
        if (num_of_three_kinds != 1) {
            return false;
        }
        if (num_of_pairs != 1) {
            return false;
        }
        if (num_of_four_kinds != 0) {
            return false;
        }

        // Fill first 3 slots of primary_cards with the three kind in raw form
        for (int i = 0, primary_cards_index = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            if (primary_cards_index == 3) {
                break;
            }

            if (combined[i].getRank() == three_kind_rank) {
                player.primary_cards[primary_cards_index++] = combined[i];
            }
        }

        // Fill next 2 slots of primary_cards with pair in raw form
        for (int i = 0, primary_cards_index = 3; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            if (primary_cards_index == 5) {
                break;
            }

            if (combined[i].getRank() == pair_rank) {
                player.primary_cards[primary_cards_index++] = combined[i];
            }
        }
        return true;
    }

    bool isThreeKind(Player &player) {
        // this function is derived from isPair
        Card combined[player.HAND_SIZE + BOARD_SIZE]{};
        combineCards(player, combined);

        int ranks_sum[13]{};
        for (int i = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            ++ranks_sum[combined[i].getRank()];
        }

        int three_kind_rank = -1;
        int num_of_three_kinds = 0;
        for (int i = 0; i <= 12; ++i) {
            if (ranks_sum[i] == 3) {
                ++num_of_three_kinds;
                three_kind_rank = i;
            }
        }
        int num_of_pairs = 0;
        for (int i = 0; i <= 12; ++i) {
            if (ranks_sum[i] == 2) {
                ++num_of_pairs;
            }
        }
        int num_of_four_kinds = 0;
        for (int i = 0; i <= 12; ++i) {
            if (ranks_sum[i] == 4) {
                ++num_of_four_kinds;
            }
        }
        if (num_of_three_kinds != 1) {
            return false;
        }
        if (num_of_pairs != 0) {
            return false;
        }
        if (num_of_four_kinds != 0) {
            return false;
        }

        // Fill first 3 slots of primary_cards with the three kind in raw form
        for (int i = 0, primary_cards_index = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            if (primary_cards_index == 3) {
                break;
            }

            if (combined[i].getRank() == three_kind_rank) {
                player.primary_cards[primary_cards_index++] = combined[i];
            }
        }

        // Fill 2 slots of secondary_cards with highest 2 cards excluding the three kind
        for (int i = player.HAND_SIZE + BOARD_SIZE - 1, secondary_cards_index = 0; i >= 0; --i) {
            if (secondary_cards_index == 2) {
                break;
            }
            if (player.primary_cards[0] == combined[i] || player.primary_cards[1] == combined[i] || player.primary_cards[2] == combined[i]) {
                continue;
            } else {
                player.secondary_cards[secondary_cards_index++] = combined[i];
            }
        }
        return true;
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
        bool flush_flag = isFlush(player);
        if (flush_flag = true) {
            return false;
        }

        // Fill first 2 slots of primary_cards with the pair in raw form
        for (int i = 0, primary_cards_index = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            if (primary_cards_index == 2) {
                break;
            }

            if (combined[i].getRank() == pair_rank) {
                player.primary_cards[primary_cards_index++] = combined[i];
            }
        }

        // Fill 3 slots of secondary_cards with highest 3 cards excluding the pair
        for (int i = player.HAND_SIZE + BOARD_SIZE - 1, secondary_cards_index = 0; i >= 0; --i) {
            if (secondary_cards_index == 3) {
                break;
            }
            if (player.primary_cards[0] == combined[i] || player.primary_cards[1] == combined[i]) {
                continue;
            } else {
                player.secondary_cards[secondary_cards_index++] = combined[i];
            }
        }
        return true;
    }

    bool isDoublePair(Player &player) {
        // this function is derived from isPair
        Card combined[player.HAND_SIZE + BOARD_SIZE]{};
        combineCards(player, combined);

        int ranks_sum[13]{};
        for (int i = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            ++ranks_sum[combined[i].getRank()];
        }

        int pair_rank = -1;
        int pair_rank_two = -1;
        int num_of_pairs = 0;

        for (int i = 0; i <= 12; ++i) {
            if (ranks_sum[i] == 2) {
                ++num_of_pairs;
            }
        }

        if (num_of_pairs < 2) {
            return false;
        }
        bool tkind_flag = isThreeKind(player);
        if (tkind_flag == true) {
            return false;
        }
        bool straight_flag = isStraight(player);
        if (straight_flag == true) {
            return false;
        }
        bool flush_flag = isFlush(player);
        if (flush_flag == true) {
            return false;
        }
        bool fhouse_flag = isFullHouse(player);
        if (fhouse_flag == true) {
            return false;
        }
        bool fkind_flag = isFourKind(player);
        if (fkind_flag == true) {
            return false;
        }
        bool sflush_flag = isStraightFlush(player);
        if (sflush_flag == true) {
            return false;
        }

        for (int i = 0; i <= 12; ++i) {
            if (ranks_sum[i] == 2) {
                pair_rank = i;
                break;
            }
        }

        for (int i = 12; i >= 0; --i) {
            if (ranks_sum[i] == 2) {
                pair_rank_two = i;
                break;
            }
        }

        // Fill first 2 slots of primary_cards with the higher pair in raw form
        for (int i = 0, primary_cards_index = 0; i < player.HAND_SIZE + BOARD_SIZE; ++i) {
            if (primary_cards_index == 2) {
                break;
            }

            if (combined[i].getRank() == pair_rank_two) {
                player.primary_cards[primary_cards_index++] = combined[i];
            }
        }

        // Fill next 2 slots of primary_cards with the lower pair in raw form
        for (int i = player.HAND_SIZE + BOARD_SIZE - 1, primary_cards_index = 2; i >= 0; --i) {
            if (primary_cards_index == 4) {
                break;
            }

            if (combined[i].getRank() == pair_rank) {
                player.primary_cards[primary_cards_index++] = combined[i];
            }
        }

        // Fill 1 slots of secondary_cards with highest 1 cards excluding the pairs
        for (int i = player.HAND_SIZE + BOARD_SIZE - 1, secondary_cards_index = 0; i >= 0; --i) {
            if (secondary_cards_index == 1) {
                break;
            }
            if (player.primary_cards[0] == combined[i] || player.primary_cards[1] == combined[i] || player.primary_cards[2] == combined[i] || player.primary_cards[3] == combined[i]) {
                continue;
            } else {
                player.secondary_cards[secondary_cards_index++] = combined[i];
            }
        }
        return true;
    }

    void assignPoints(Player &player) {
        bool pair_flag = isPair(player);
        bool dpair_flag = isDoublePair(player);
        bool tkind_flag = isThreeKind(player);
        bool straight_flag = isStraight(player);
        bool flush_flag = isFlush(player);
        bool fhouse_flag = isFullHouse(player);
        bool fkind_flag = isFourKind(player);
        bool sflush_flag = isStraightFlush(player);
        if (pair_flag) {
            player.hand_points = (1 + player.primary_cards[0].getRank()) * 10;
        } else if (dpair_flag) {
            player.hand_points = (1 + player.primary_cards[0].getRank()) * 100;
        } else if (tkind_flag) {
            player.hand_points = (1 + player.primary_cards[0].getRank()) * 1000;
        } else if (straight_flag) {
            player.hand_points = (1 + player.primary_cards[0].getRank()) * 10000;
        } else if (flush_flag) {
            player.hand_points = (1 + player.primary_cards[0].getRank()) * 100000;
        } else if (fhouse_flag) {
            player.hand_points = (1 + player.primary_cards[0].getRank()) * 1000000;
        } else if (fkind_flag) {
            player.hand_points = (1 + player.primary_cards[0].getRank()) * 10000000;
        } else if (sflush_flag) {
            player.hand_points = (1 + player.primary_cards[0].getRank()) * 100000000;
        } else {  // has nothing, return high card
            player.hand_points = 1 + getHighestRank(player);
        }
    }

    void tieBreaker(Player &player_one, Player &player_two, Player &result) {
        for (int i = 0; i < player_one.TOP_SIZE; ++i) {
            if (player_one.secondary_cards[i].getRank() > player_two.secondary_cards[i].getRank()) {
                result = player_one;
                break;
            }
            if (player_one.secondary_cards[i].getRank() < player_two.secondary_cards[i].getRank()) {
                result = player_two;
                break;
            }
            if (player_one.secondary_cards[i].getRank() == player_two.secondary_cards[i].getRank()) {
                continue;
            }
            if (player_one.secondary_cards[i] == -1 && player_two.secondary_cards[i] == -1) {
                Player complete_tie = Player();  // returns uninitialized Player to indicate complete tie
                result = complete_tie;
                break;
            }
        }
    }
};
#endif