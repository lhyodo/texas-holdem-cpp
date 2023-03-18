
#include <cstdlib>

void FillHand(int* hand, bool* deck, int HAND_SIZE, int DECK_SIZE)
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
