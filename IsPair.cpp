#include <iostream>
#include <cstdlib>
#include "GetRank.cpp"
#include "GetSuit.cpp"

int IsPair(int *hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE, int *top_five_cards)
{

    // ===================== NOTE =====================
    // Deck is organized from 2 of clubs at index 0 and ace of spades at index 51
    // Order of suits is alphabetical. clubs, diamonds, hearts, spades
    // Rank of a card is obtained by the formula card_num/4
    // A "Jack" card has a rank of 9
    // A    "2" card has a rank of 0
    // An "Ace" card has a rank of 12

    // Suit of a card is obtained by the formula card_num%4
    // A "Spades" card has a suit of 3
    // A  "Clubs" card has a suit of 0

    // Append hand cards array with community cards array for ease of coding
    // In this context combined_cards is hand + community cards
    // Index of 0 and 1 will be from the hand, 2 to 6 will be the board cards
    int combined_cards[HAND_SIZE + COMMUNITY_SIZE]{};
    int combined_cards_index = 0;
    for (int i = 0; i < HAND_SIZE; ++i)
    {
        combined_cards[combined_cards_index++] = hand[i];
    }
    for (int i = 0; i < COMMUNITY_SIZE; ++i)
    {
        combined_cards[combined_cards_index++] = community_cards[i];
    }

    // Initialize ranks_sum with hand and board cards
    // eg cards of "2 of clubs" "4 of hearts" "4 of spades"
    // ranks_sum = {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    int ranks_sum[13]{};
    int num_of_pairs = 0;
    for (int i = 0; i < HAND_SIZE + COMMUNITY_SIZE; ++i)
    {
        int card = combined_cards[i];
        int rank = GetRank(card);
        ++ranks_sum[rank];
    }

    // If num_of_pairs is 2, its a double pair (not a pair). If 0, no pair.
    // Therefore return 0 to indicate no pair
    
    for (int i = 0; i < 13; ++i)
    {
        if (ranks_sum[i] == 2)
        {
            ++num_of_pairs;
        }
    }
    // std::cout << "num of pairs: " << num_of_pairs << std::endl;
    if (num_of_pairs != 1)
    {
        return 0;
    }

    // Get rank and suit of pair cards
    int pair_rank = -1;
    int pair_suits[2]{};
    int pair_suits_index = 0;
    for (int i = 12; i >= 0; --i)
    {
        if (ranks_sum[i] == 2)
        {
            pair_rank = i;
            for (int j = 0; j < HAND_SIZE + COMMUNITY_SIZE; ++j)
            {
                if (GetRank(combined_cards[j]) == i)
                {
                    pair_suits[pair_suits_index++] = GetSuit(combined_cards[j]);
                }
            }
            break;
        }
    }

    // debugging, display suits
    std::cout << "debug display suits\n";
    std::cout << pair_suits[0] << " " << pair_suits[1] << std::endl;

    // Fill first 2 slots of top_five_cards with the pair in raw form
    top_five_cards[0] = pair_rank * 4 + pair_suits[0];
    top_five_cards[1] = pair_rank * 4 + pair_suits[1];

    // Fill last 3 slots of top_five_cards with highest 3 cards excluding the pair
    QuickSort(combined_cards, 0, HAND_SIZE + COMMUNITY_SIZE - 1);
    int top_cards_index = 2;
    for (int i = HAND_SIZE + COMMUNITY_SIZE - 1; i >= 0; --i)
    {
        if (top_cards_index == 5)
        {
            break;
        }
        if (top_five_cards[0] == combined_cards[i] || top_five_cards[1] == combined_cards[i])
        {
            continue;
        }
        else
        {
            top_five_cards[top_cards_index++] = combined_cards[i];
        }
    }

    return 1;
}