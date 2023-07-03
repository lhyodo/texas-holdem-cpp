#include <iostream>
#include <cstdlib>
#include "GetSuit.cpp"
#include "CombineCards.cpp"
#include "QuickSort.cpp"

bool IsFlush(int *hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE, int *top_five_cards)
{
    int combined_cards[HAND_SIZE + COMMUNITY_SIZE]{};
    CombineCards(hand, community_cards, HAND_SIZE, COMMUNITY_SIZE, combined_cards);
    QuickSort(combined_cards, 0, HAND_SIZE + COMMUNITY_SIZE - 1);




    int cc_index = 0;
    for (int i = 0; i < HAND_SIZE; ++i)
    {
        combined_cards[cc_index++] = hand[i];
    }
    for (int i = 0; i < COMMUNITY_SIZE; ++i)
    {
        combined_cards[cc_index++] = community_cards[i];
    }
    
    int suits_sum[4]{};
    for (int i = 0; i < HAND_SIZE + COMMUNITY_SIZE; ++i)
    {
        int card = combined_cards[i];
        int suit = GetSuit(card);
        ++suits_sum[suit];
    }

    bool has_flush = false;
    int flush_suit = -1;
    for (int i = 0; i < 4; ++i)
    {
        if (suits_sum[i] >= 5)
        {
            has_flush = true;
            flush_suit = i;
            break;
        }
    }
    if (has_flush == false)
    {
        return false;
    }

    int top_cards_index = 0;
    for (int j = HAND_SIZE + COMMUNITY_SIZE - 1; j >= 0; --j)
    {
        if (top_cards_index == 5)
        {
            break;
        }
        if (GetSuit(combined_cards[j]) == flush_suit)
        {

            top_five_cards[top_cards_index++] = combined_cards[j];
        }
    }
    // QuickSort(top_five_cards, 0, COMMUNITY_SIZE - 1);
    return true;
}