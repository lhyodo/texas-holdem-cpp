#include <iostream>

int IsDoublePair(int *hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE, int *double_pair_ranks)
{
    int ranks[13]{};
    // ranks[0] is 2, ranks[12] is Ace
    for (int i = 0; i < HAND_SIZE; ++i)
    {
        int c = hand[i];
        c = c / 4;
        ranks[c] += 1;
    }

    for (int i = 0; i < COMMUNITY_SIZE; ++i)
    {
        int c = community_cards[i];
        c = c / 4;
        ranks[c] += 1;
    }

    int num_of_pairs {};
    int index {};
    for (int i = 13; i >= 0; --i)
    {
        if (num_of_pairs == 2)
        {
            break;
        }
        if (ranks[i] == 2)
        {
            double_pair_ranks[num_of_pairs++] = i;
        }
    }

    // returns 0 if zero or no pairs
    // otherwise, return the value of the highest pair
    // eg pair of 10's and 5's
    // return 10
    // return both sets in double_pair_ranks
    if (num_of_pairs == 0 || num_of_pairs == 1)
    {
        return -1;
    }
    return double_pair_ranks[0];
}