#include "GetCardString.cpp"

void DisplayHand(int* hand_raw, int HAND_SIZE)
{
    for (int i = 0; i < HAND_SIZE; ++i)
    {
        std::cout << GetCardString(hand_raw[i]) << std::endl;
    }

}