
#include <cstdlib>
#include <iostream>
#include <random>
#include <functional>

int main(int, char **)
{
    std::cout << "Hello, world!\n";

    int deck[52];
    for (int i = 0; i < 52; ++i)
    {
        deck[i] = i;
        std::cout << deck[i] << std::endl;
    }

    std::cout << "What is the rank and suit of card 33? ";

    switch (33 / 4)
    {
    case 0:
        std::cout << "rank: ace   ";
        break;
    case 1:
        std::cout << "rank: 2   ";
        break;
    case 2:
        std::cout << "rank: 3   ";
        break;
    case 3:
        std::cout << "rank: 4   ";
        break;
    case 4:
        std::cout << "rank: 5   ";
        break;
    case 5:
        std::cout << "rank: 6   ";
        break;
    case 6:
        std::cout << "rank: 7   ";
        break;
    case 7:
        std::cout << "rank: 8   ";
        break;
    case 8:
        std::cout << "rank: 9   ";
        break;
    case 9:
        std::cout << "rank: 10   ";
        break;
    case 10:
        std::cout << "rank: jack   ";
        break;
    case 11:
        std::cout << "rank: queen   ";
        break;
    case 12:
        std::cout << "rank: king   ";
        break;
    }

    switch (33 % 4)
    {
    case 0:
        std::cout << "suit: clubs" << std::endl;
        break;
    case 1:
        std::cout << "suit: diamonds" << std::endl;
        break;
    case 2:
        std::cout << "suit: hearts" << std::endl;
        break;
    case 3:
        std::cout << "suit: spades" << std::endl;
        break;
    }


    std::cout << "Goodbye, cruel world!" << std::endl;
    return 0;
}
