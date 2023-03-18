#include <iostream>

void DisplayDeck(bool* deck, int DECK_SIZE)
{
    for (int i = 0; i < DECK_SIZE; ++i)
    {
        deck[i] = 0;
        std::cout << "Card num: " << i << "   " << "Value: " << deck[i] << std::endl;
    }
}