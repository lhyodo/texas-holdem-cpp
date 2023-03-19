#include <iostream>
#include <cstdlib>

int IsFlush(int *hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE)
{
    int suits[4]{};

    for (int i = 0; i < HAND_SIZE; ++i)
    {
        int c = hand[i];
        c = c % 4;
        suits[c] += 1;
    }

    for (int i = 0; i < COMMUNITY_SIZE; ++i)
    {
        int c = community_cards[i];
        c = c % 4;
        suits[c] += 1;
    }
    std::cout << "IsPair: \n";
    for (int i = 0; i < 4; ++i)
    {
        std::cout << suits[i] << std::endl;
    }

    int indicator {};
    for (int i = 0; i < 4; ++i)
    {
        
        if (suits[i] > 4)
        {
            ++indicator;
        }
    }
    // if indicator equals 1, single pair
    // if equals 2 or 3, double pair (no triple pairs allowed)
    // if equals 10, 3 of a kind
    // if equals 20, 4 of a kind
    std::cout << "This is the flush indicator: " << indicator << std::endl;
    return indicator;
}