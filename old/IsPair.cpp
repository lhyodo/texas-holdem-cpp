#include <iostream>
#include <cstdlib>
#include "GetRank.cpp"
#include "GetSuit.cpp"
#include "QuickSort.cpp"

bool IsPair(int *hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE, int *top_five_cards)
{

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
    int combined_cards[HAND_SIZE + COMMUNITY_SIZE]{};
    CombineCards(hand, community_cards, HAND_SIZE, COMMUNITY_SIZE, combined_cards);
    QuickSort(combined_cards, 0, HAND_SIZE + COMMUNITY_SIZE - 1);
    // int cc_index = 0;
    // for (int i = 0; i < HAND_SIZE; ++i)
    // {
    //     combined_cards[cc_index++] = hand[i];
    // }
    // for (int i = 0; i < COMMUNITY_SIZE; ++i)
    // {
    //     combined_cards[cc_index++] = community_cards[i];
    // }

    // ranks_sum = how many cards there are of each rank
    // eg cards of "2 of clubs" "4 of hearts" "4 of spades"
    // ranks_sum = {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    int ranks_sum[13]{};
    for (int i = 0; i < HAND_SIZE + COMMUNITY_SIZE; ++i)
    {
        int card = combined_cards[i];
        int rank = GetRank(card);
        ++ranks_sum[rank];
    }

    bool has_pair = false;
    int pair_rank = -1;
    for (int i = 12; i >= 0; --i)
    {
        if (ranks_sum[i] == 2)
        {
            has_pair = true;
            pair_rank = i;
            break;
        }
    }
    if (has_pair == false)
    {
        return false;
    }

    // Fill first 2 slots of top_five_cards with the pair in raw form
    int top_cards_index = 0;
    for (int j = HAND_SIZE + COMMUNITY_SIZE - 1; j >= 0 ; --j)
    {
        if (top_cards_index == 2)
        {
            break;
        }
        
        if (GetRank(combined_cards[j]) == pair_rank)
        {
            top_five_cards[top_cards_index++] = combined_cards[j];
        }
    }

    // Fill last 3 slots of top_five_cards with highest 3 cards excluding the pair
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

    return true;
}