#include <iostream>
#include <cstdlib>

int IsFlush(int *hand, int *community_cards, int HAND_SIZE, int COMMUNITY_SIZE)
{
    // gather data from hand and board cards and store into a rank array
    // ranks[0] is 2, ranks[12] is Ace
    int cards[13][4]{};

    for (int i = 0; i < HAND_SIZE; ++i)
    {
        int rank = hand[i];
        rank = rank / 4;
        int suit = hand[i];
        suit = suit % 4;
        cards[rank][suit] += 1;
    }

    for (int i = 0; i < COMMUNITY_SIZE; ++i)
    {
        int rank = community_cards[i];
        rank = rank / 4;
        int suit = community_cards[i];
        suit = suit % 4;
        cards[rank][suit] += 1;
    }
    std::cout << "IsFlush: " << std::endl;
    for (int i = 0; i < 13; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            std::cout << cards[i][j] << " ";
        }
        std::cout << std::endl;
    }


    int flush_counter {};






    
    // // suits
    // int suits[4]{};
    // for (int i = 0; i < HAND_SIZE; ++i)
    // {
    //     int c = hand[i];
    //     c = c % 4;
    //     suits[c] += 1;
    // }

    // for (int i = 0; i < COMMUNITY_SIZE; ++i)
    // {
    //     int c = community_cards[i];
    //     c = c % 4;
    //     suits[c] += 1;
    // }



    // std::cout << "IsFlush: \n";
    // for (int i = 0; i < 4; ++i)
    // {
    //     std::cout << suits[i] << std::endl;
    // }

    // int indicator {};
    // for (int i = 0; i < 4; ++i)
    // {
    //     if (suits[i] > 4)
    //     {
    //         ++indicator;
    //     }
    // }


    // returns 0 if no flush
    // otherwise return highest rank of flush
    // std::cout << "This is the flush indicator: " << indicator << std::endl;
    return 0;
}