
#ifndef COMBINECARDS
#define COMBINECARDS

#include "QuickSort.cpp"

void CombineCards(int *your_hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE, int *result_array)
{
    int index = 0;
    for (int i = 0; i < HAND_SIZE; ++i)
    {
        result_array[index++] = your_hand[i];
    }
    for (int i = 0; i < COMMUNITY_SIZE; ++i)
    {
        result_array[index++] = community_cards[i];
    }
}

#endif