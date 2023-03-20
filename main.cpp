#include <cstdlib>
#include <iostream>
#include "DisplayHand.cpp"
#include "DisplayDeck.cpp"
#include "FillHand.cpp"
#include "IsPair.cpp"
#include "IsDoublePair.cpp"
#include "IsFlush.cpp"
#include "IsStraight.cpp"

const int DECK_SIZE = 52;
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

    // std::cout << "your hand again: \n";
    // for (int i = 0; i < 2; ++i)
    // {
    //     std::cout << your_hand[i] << std::endl;
    // }



    // int* dealer_hand = new int[HAND_SIZE];
    // FillHand(dealer_hand, deck, HAND_SIZE, DECK_SIZE);
    // std::cout << "This is the dealer's hand: \n";
    // DisplayHand(dealer_hand, HAND_SIZE);

    int* community_cards = new int[COMMUNITY_SIZE];
    FillHand(community_cards, deck, COMMUNITY_SIZE, DECK_SIZE);
    std::cout << "These are the community cards: \n";


    // display board cards
    // std::cout << "This is the flop: \n";
    for (int i = 0; i < 3; ++i)
    {
        DisplayCard(community_cards[i]);
    }
    // std::cout << "This is the turn: \n";
    DisplayCard(community_cards[3]);
    // std::cout << "This is the river: \n";
    DisplayCard(community_cards[4]);


    // IsPair
    int you_have_pair = IsPair(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE);
    if (you_have_pair != -1)
    {
        std::cout << "you have a PAIR of " << you_have_pair + 2 << "'s \n";
    }

    // IsDoublePair
    int* double_pair_ranks = new int[2];
    int you_have_double_pair = IsDoublePair(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE, double_pair_ranks);
    if (you_have_double_pair != -1)
    {
        std::cout << "you have a DOUBLE PAIR of " << double_pair_ranks[0] + 2 << "'s and " << double_pair_ranks[1] + 2 << "'s \n";
    }


    // IsFlush
    int you_have_flush = IsFlush(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE);
    if (you_have_flush != -1)
    {
        std::cout << "you have a *FLUSH* of rank " << you_have_flush + 2 << " \n";
    }

    
    // IsStraight
    int you_have_straight = IsStraight(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE);
    if (you_have_straight == 1)
    {
        std::cout << "you have a |STRAIGHT| \n";
    }



    // END, SHOW DECK AND RETURN 0
    // std::cout << "This is the final deck: \n";
    // DisplayDeck(deck, DECK_SIZE);

    std::cout << "Goodbye, cruel world!" << std::endl;
    return 0;
}