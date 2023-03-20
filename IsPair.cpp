#include <iostream>
#include <cstdlib>

int IsPair(int *hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE)
{
    // 2 is now ranks[0]
    int ranks[13]{};
    // 
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
    std::cout << "IsPair: \n";
    for (int i = 0; i < 13; ++i)
    {
        std::cout << ranks[i] << std::endl;
    }
    int indicator = -1;
    for (int i = 12; i >= 0; --i)
    {
        if (ranks[i] == 2)
        {
            indicator = i;
            break;
        }
    }

    return indicator;
}