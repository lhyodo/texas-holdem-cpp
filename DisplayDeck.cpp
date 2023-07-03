#include <iostream>

// 0 indicates the card is not in play
// 1 indicates the card is in play
// index 0 is first card
// index 51 is last card

void DisplayDeck(bool *deck, int DECK_SIZE)
{
    for (int i = 0; i < DECK_SIZE; ++i)
    {
        std::cout << "Card num: " << i << "   "
                  << "Value: " << deck[i] << std::endl;
    }
}