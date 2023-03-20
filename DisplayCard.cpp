
#include <iostream>

void DisplayCard(int card)
{
    // quotient of 0 indicates rank of 2
    // quotient of 1 indicates rank of 3
    // so forth
    // quotient of 12 indicates rank of Ace
    
    switch (card / 4)
    {
    case 0:
        std::cout << "2 of ";
        break;
    case 1:
        std::cout << "3 of ";
        break;
    case 2:
        std::cout << "4 of ";
        break;
    case 3:
        std::cout << "5 of ";
        break;
    case 4:
        std::cout << "6 of ";
        break;
    case 5:
        std::cout << "7 of ";
        break;
    case 6:
        std::cout << "8 of ";
        break;
    case 7:
        std::cout << "9 of ";
        break;
    case 8:
        std::cout << "10 of ";
        break;
    case 9:
        std::cout << "J of ";
        break;
    case 10:
        std::cout << "Q of ";
        break;
    case 11:
        std::cout << "K of ";
        break;
    case 12:
        std::cout << "A of ";
        break;
    }


    // remainder of 0 indicates clubs
    // remainder of 1 indicates diamonds
    // remainder of 2 indicates hearts
    // remainder of 3 indicates spades
    switch (card % 4)
    {
    case 0:
        std::cout << "clubs" << std::endl;
        break;
    case 1:
        std::cout << "diamonds" << std::endl;
        break;
    case 2:
        std::cout << "hearts" << std::endl;
        break;
    case 3:
        std::cout << "spades" << std::endl;
        break;
    }
}
