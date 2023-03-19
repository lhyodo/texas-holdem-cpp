#include <cstdlib>
#include <iostream>
#include "DisplayHand.cpp"
#include "DisplayDeck.cpp"
#include "FillHand.cpp"
#include "IsPair.cpp"

const int DECK_SIZE = 20;
const int HAND_SIZE = 2;
const int COMMUNITY_SIZE = 5;

int main(int, char **)
{
    std::cout << "Hello, world!\n";

    bool* deck = new bool[DECK_SIZE] {};

    int* your_hand = new int[HAND_SIZE] {};
    FillHand(your_hand, deck, HAND_SIZE, DECK_SIZE);
    std::cout << "This is your hand: \n";
    DisplayHand(your_hand, HAND_SIZE);

    std::cout << "your hand again: \n";
    for (int i = 0; i < 2; ++i)
    {
        std::cout << your_hand[i] << std::endl;
    }



    int* dealer_hand = new int[HAND_SIZE];
    FillHand(dealer_hand, deck, HAND_SIZE, DECK_SIZE);
    std::cout << "This is the dealer's hand: \n";
    DisplayHand(dealer_hand, HAND_SIZE);

    int* community_cards = new int[COMMUNITY_SIZE];
    FillHand(community_cards, deck, COMMUNITY_SIZE, DECK_SIZE);
    std::cout << "These are the community cards: \n";


    // display board cards
    std::cout << "This is the flop: \n";
    for (int i = 0; i < 3; ++i)
    {
        DisplayCard(community_cards[i]);
    }
    std::cout << "This is the turn: \n";
    DisplayCard(community_cards[3]);
    std::cout << "This is the river: \n";
    DisplayCard(community_cards[4]);


    // IsPair
    int you_have_pair = IsPair(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE);
    if (you_have_pair == 1)
    {
        std::cout << "you have a pair! \n";
    }
    else if (you_have_pair == 2 || you_have_pair == 3)
    {
        std::cout << "you have a double pair! \n";
    }
    else if (you_have_pair >= 10 && you_have_pair < 20)
    {
        std::cout << "you have a 3 of a kind! \n";
    }
    else if (you_have_pair >= 20)
    {
        std::cout << "you have a 4 of a kind! the best kind! \n";
    }

    




    // END, SHOW DECK AND RETURN 0
    std::cout << "This is the final deck: \n";
    DisplayDeck(deck, DECK_SIZE);

    std::cout << "Goodbye, cruel world!" << std::endl;
    return 0;
}