#include <iostream>
#include "QuickSort.cpp"
#include "GetRank.cpp"
bool IsStraight(int *hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE, int *top_five_cards)
{

    int combined_cards[HAND_SIZE + COMMUNITY_SIZE]{};
    CombineCards(hand, community_cards, HAND_SIZE, COMMUNITY_SIZE, top_five_cards);
    QuickSort(combined_cards, 0, HAND_SIZE + COMMUNITY_SIZE - 1);

    int ranks_sum[13]{};
    for (int i = 0; i < HAND_SIZE + COMMUNITY_SIZE; ++i)
    {
        int card = combined_cards[i];
        int rank = GetRank(card);
        ++ranks_sum[rank];
    }

    bool is_straight = false;
    int highest_rank_in_straight = -1;
    for (int i = 12; i >= 0; --i)
    {
        if (ranks_sum[i] > 0 && ranks_sum[i - 1] > 0 && ranks_sum[i - 2] > 0 && ranks_sum[i - 3] > 0 && ranks_sum[i - 4] > 0)
        {
            highest_rank_in_straight = i;
            is_straight = true;
            break;
        }
    }
    if (is_straight == false)
    {
        return false;
    }

    for (int i = HAND_SIZE + COMMUNITY_SIZE - 1; i >= 0; --i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (GetRank(combined_cards[i]) == highest_rank_in_straight - j)
            {
                top_five_cards[j] = combined_cards[i];
            }
        }
    }

    return is_straight;
}