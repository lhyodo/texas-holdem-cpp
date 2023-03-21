#include <iostream>
int IsStraight(int *hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE)
{
    int ranks[13]{};

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
    // std::cout << "IsStraight: \n";
    // for (int i = 0; i < 13; ++i)
    // {
    //     std::cout << ranks[i] << std::endl;
    // }

    int indicator = -1;
    for (int i = 4; i < 13; ++i)
    {
        if (ranks[i] > 0 && ranks[i - 1] > 0 && ranks[i - 2] > 0 && ranks[i - 3] > 0 && ranks[i - 4] > 0)
        {
            indicator = i;
        }
    }
    if (ranks[12] > 0 && ranks[0] > 0 && ranks[1] > 0 && ranks[2] > 0 && ranks[3] > 0)
    {
        indicator = 3;
    }

    return indicator;
}