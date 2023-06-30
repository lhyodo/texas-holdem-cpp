#include <iostream>

int IsDoublePair(int *hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE, int *double_pair_ranks, int *top_five_cards)
{
    int ranks[13]{};
    // ranks[0] is 2, ranks[12] is Ace
    for (int i = 0; i < HAND_SIZE; ++i)
    {
        int c = hand[i];
        c = c / 4;
        ranks[c] += 1;
    }

    for (int i = 0; i < COMMUNITY_SIZE; ++i)
    {
        int c = community_cards[i];
        c = c / 4;
        ranks[c] += 1;
    }

    int suits[4]{};
    for (int i = 0; i < HAND_SIZE; ++i)
    {
        int c = hand[i];
        c = c % 4;
        suits[c] += 1;
    }

    for (int i = 0; i < COMMUNITY_SIZE; ++i)
    {
        int c = community_cards[i];
        c = c % 4;
        suits[c] += 1;
    }



    int num_of_pairs {};
    int index {};
    for (int i = 13; i >= 0; --i)
    {
        if (num_of_pairs == 2)
        {
            break;
        }
        if (ranks[i] == 2)
        {
            double_pair_ranks[num_of_pairs++] = i;
        }
    }
    // returns 0 if zero or no pairs
    // otherwise, return the value of the highest pair
    // eg pair of 10's and 5's
    // return 10
    // return both sets in double_pair_ranks
    if (num_of_pairs == 0 || num_of_pairs == 1)
    {
        return -1;
    }



    // int cards[13][4]{};
    // for (int i = 0; i < HAND_SIZE; ++i)
    // {
    //     int rank = hand[i];
    //     rank = rank / 4;
    //     int suit = hand[i];
    //     suit = suit % 4;
    //     cards[rank][suit] += 1;
    // }
    
    // for (int i = 0; i < COMMUNITY_SIZE; ++i)
    // {
    //     int rank = community_cards[i];
    //     rank = rank / 4;
    //     int suit = community_cards[i];
    //     suit = suit % 4;
    //     cards[rank][suit] += 1;
    // }
    // std::cout << "Display IsDoublePair 2d array: " << std::endl;
    // for (int i = 0; i < 13; ++i)
    // {
    //     for (int j = 0; j < 4; ++j)
    //     {
    //         std::cout << cards[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // int top_cards_index = 0;
    // for (int i = 0; i < 13; ++i)
    // {
    //     int foo = 0;
    //     int arr[2][2] {};
    //     int arr_index = 0;
    //     for (int j = 0; j < 4; ++j)
    //     {
    //         foo += cards[i][j];
    //         arr[arr_index][]
    //     }
    //     if (foo == 2)
    //     {

    //     }
    // }
    
    // int ranks2[13]{};
    // int pair2[4]{};
    // int ind2 = 0;
    // for (int i = 12; i >= 0; --i)
    // {
    //     for (int j = 3; j >= 0; --j)
    //     {
    //         if (cards[i][j] == 1)
    //         {
    //             ++ranks2[i];
    //             pair2[ind2++] = i;
    //             pair2[ind2++] = j;
    //             if (ind2 == 4)
    //             {
    //                 break;
    //             }
    //         }
    //     }
    // }

    

    return double_pair_ranks[0];
}