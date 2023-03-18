#include "DisplayCard.cpp"

void DisplayHand(int* hand, int HAND_SIZE)
{
    for (int i = 0; i < HAND_SIZE; ++i)
    {
        DisplayCard(hand[i]);
    }

}