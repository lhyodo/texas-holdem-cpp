#include <cstdlib>
#include <iostream>
#include "DisplayCard.cpp"

const int DECK_SIZE = 52;
const int HAND_SIZE = 5;

int main(int, char **)
{
    std::cout << "Hello, world!\n";

    int deck[DECK_SIZE];
    for (int i = 0; i < DECK_SIZE; ++i)
    {
        deck[i] = i;
        std::cout << deck[i] << std::endl;
    }

    std::srand((unsigned int)time(NULL));


// YOUR HAND =====
    int arr[HAND_SIZE];
    int arr_counter = 0;

    while (arr_counter < HAND_SIZE)
    {
        int rand_card = std::rand() % DECK_SIZE;
        if (deck[rand_card] != -1)
        {
            arr[arr_counter] = rand_card;
            ++arr_counter;
            deck[rand_card] = -1;
        }
    }
    std::cout << "This is your hand: \n";
    DisplayCard(arr[0]);
    DisplayCard(arr[1]);
    DisplayCard(arr[2]);
    DisplayCard(arr[3]);
    DisplayCard(arr[4]);


// DEALER HAND =====
    int arr2[HAND_SIZE];
    int arr2_counter = 0;

    while (arr2_counter < HAND_SIZE)
    {
        int rand_card = std::rand() % DECK_SIZE;
        if (deck[rand_card] != -1)
        {
            arr2[arr2_counter] = rand_card;
            ++arr2_counter;
            deck[rand_card] = -1;
        }
    }
    std::cout << "This is their hand: \n";
    DisplayCard(arr2[0]);
    DisplayCard(arr2[1]);
    DisplayCard(arr2[2]);
    DisplayCard(arr2[3]);
    DisplayCard(arr2[4]);






// END, SHOW DECK AND RETURN 0
    std::cout << "This is the final deck: \n";
    for (int i = 0; i < DECK_SIZE; ++i)
    {
        std::cout << deck[i] << std::endl;
    }

    std::cout << "Goodbye, cruel world!" << std::endl;
    return 0;
}