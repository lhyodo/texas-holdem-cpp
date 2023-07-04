
#include "QuickSort.cpp"

int GetHighestRank(int *your_hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE, int *sorted_array)
{
    int index = 0;
    for (int i = 0; i < HAND_SIZE; ++i)
    {
        sorted_array[index++] = your_hand[i];
    }
    for (int i = 0; i < COMMUNITY_SIZE; ++i)
    {
        sorted_array[index++] = community_cards[i];
    }

    for (int i = 0; i < HAND_SIZE + COMMUNITY_SIZE; ++i)
    {
        sorted_array[i] = sorted_array[i] / 4;
    }
    QuickSort(sorted_array, 0, HAND_SIZE + COMMUNITY_SIZE - 1);
    return sorted_array[HAND_SIZE + COMMUNITY_SIZE - 1];
}
