#include <cstdlib>
#include <iostream>
#include "DisplayHand.cpp"
#include "DisplayDeck.cpp"
#include "FillHand.cpp"

const int DECK_SIZE = 52;
const int HAND_SIZE = 5;

int main(int, char **)
{
    std::cout << "Hello, world!\n";

    bool deck[DECK_SIZE];


    DisplayDeck(deck, DECK_SIZE);

    int your_hand[HAND_SIZE];
    FillHand(your_hand, deck, HAND_SIZE, DECK_SIZE);
    std::cout << "This is your hand: \n";
    DisplayHand(your_hand, HAND_SIZE);

    int dealer_hand[HAND_SIZE];
    FillHand(your_hand, deck, HAND_SIZE, DECK_SIZE);
    std::cout << "This is the dealer's hand: \n";
    DisplayHand(your_hand, HAND_SIZE);

// END, SHOW DECK AND RETURN 0
    std::cout << "This is the final deck: \n";
    DisplayDeck(deck, DECK_SIZE);

    std::cout << "Goodbye, cruel world!" << std::endl;
    return 0;
}