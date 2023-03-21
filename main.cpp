#include <cstdlib>
#include <iostream>
#include "DisplayHand.cpp"
#include "DisplayDeck.cpp"
#include "GetRankString.cpp"
#include "GetHighestRank.cpp"
#include "FillHand.cpp"
#include "IsPair.cpp"
#include "IsThreeKind.cpp"
#include "IsFourKind.cpp"
#include "IsDoublePair.cpp"
#include "IsFlush.cpp"
#include "IsStraight.cpp"

const int DECK_SIZE = 52;
const int HAND_SIZE = 2;
const int COMMUNITY_SIZE = 5;

int main(int, char **)
{
    std::cout << "Hello, world!\n";

    bool *deck = new bool[DECK_SIZE]{};

    int *your_hand = new int[HAND_SIZE]{};
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

    int *community_cards = new int[COMMUNITY_SIZE];
    FillHand(community_cards, deck, COMMUNITY_SIZE, DECK_SIZE);
    std::cout << "These are the community cards: \n";

    // display board cards
    // std::cout << "This is the flop: \n";
    for (int i = 0; i < 3; ++i)
    {
        std::cout << GetCardString(community_cards[i]) << std::endl;
    }
    // std::cout << "This is the turn: \n";
    std::cout << GetCardString(community_cards[3]) << std::endl;
    // std::cout << "This is the river: \n";
    std::cout << GetCardString(community_cards[4]) << std::endl;

    int *top_five_cards = new int[5];

    // IsPair
    int you_have_pair = IsPair(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE, top_five_cards);
    if (you_have_pair == 1)
    {
        std::cout << "Your top five cards: \n";
        for (int i = 0; i < 5; ++i)
        {
            std::cout << GetCardString(top_five_cards[i]) << "\n";
        }
        std::cout << "you have a PAIR of " << GetRankString(GetRank(top_five_cards[0])) << "s \n";
    }

    // END, SHOW DECK AND RETURN 0
    // std::cout << "This is the final deck: \n";
    // DisplayDeck(deck, DECK_SIZE);

    std::cout << "Goodbye, cruel world!" << std::endl;
    return 0;
}