#include <cstdlib>
#include <iostream>
#include "DisplayHand.cpp"
#include "DisplayDeck.cpp"
#include "DisplayRank.cpp"
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
        std::cout << "you have a PAIR of " << DisplayRank(you_have_pair) << "s \n";
    }

    // IsDoublePair
    int* double_pair_ranks = new int[2];
    int you_have_double_pair = IsDoublePair(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE, double_pair_ranks);
    if (you_have_double_pair != -1)
    {
        std::cout << "you have a DOUBLE PAIR of " << DisplayRank(double_pair_ranks[0]) << "s and " << DisplayRank(double_pair_ranks[1]) << "s \n";
    }
    
    // IsThreeKind
    int you_have_three_kind = IsThreeKind(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE);
    if (you_have_three_kind != -1)
    {
        std::cout << "you have a 3 OF A KIND of " << DisplayRank(you_have_three_kind) << "s \n";
    }
    // IsFourKind
    int you_have_four_kind = IsFourKind(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE);
    if (you_have_four_kind != -1)
    {
        std::cout << "you have a 4 OF A KIND of " << DisplayRank(you_have_four_kind) << "s \n";
    }

    // IsFlush
    int you_have_flush = IsFlush(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE);
    if (you_have_flush != -1)
    {
        std::cout << "you have a *FLUSH* of rank " << DisplayRank(you_have_flush) << std::endl;
    }

    
    // IsStraight
    int you_have_straight = IsStraight(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE);
    if (you_have_straight != -1)
    {
        std::cout << "you have a |STRAIGHT| of rank " << DisplayRank(you_have_straight) << std::endl;
    }
    int sorted_array[7] {};
    int your_high_card = GetHighestRank(your_hand, community_cards, HAND_SIZE, COMMUNITY_SIZE, sorted_array);
    // if (you_have_pair == -1 && you_have_double_pair == -1 && you_have_flush == -1 && you_have_straight == -1)
    // {
        std::cout << "you have a high card of " << DisplayRank(your_high_card) << std::endl;
    // }



    // END, SHOW DECK AND RETURN 0
    // std::cout << "This is the final deck: \n";
    // DisplayDeck(deck, DECK_SIZE);

    std::cout << "Goodbye, cruel world!" << std::endl;
    return 0;
}