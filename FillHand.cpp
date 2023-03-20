
#include <cstdlib>

// Fills hand one by one from deck by generating a rand_card
// if rand_card is unique, put card in hand, and set card to 1 in deck to indicate usage
// if rand_card is the same number, regenerate rand_card

void FillHand(int *hand, bool *deck, int HAND_SIZE, int DECK_SIZE)
{
    std::srand((unsigned int)time(NULL));
    int arr_counter = 0;
    while (arr_counter < HAND_SIZE)
    {
        int rand_card = std::rand() % DECK_SIZE;
        if (deck[rand_card] != 1)
        {
            hand[arr_counter] = rand_card;
            ++arr_counter;
            deck[rand_card] = 1;
        }
    }
}
