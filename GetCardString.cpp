
#include <iostream>

std::string GetCardString(int card_raw)
{
    // quotient of 0 indicates rank of 2
    // quotient of 1 indicates rank of 3
    // so forth
    // quotient of 12 indicates rank of Ace
    std::string str{};
    switch (card_raw / 4)
    {
    case 0:
        str = "2 of ";
        break;
    case 1:
        str = "3 of ";
        break;
    case 2:
        str = "4 of ";
        break;
    case 3:
        str = "5 of ";
        break;
    case 4:
        str = "6 of ";
        break;
    case 5:
        str = "7 of ";
        break;
    case 6:
        str = "8 of ";
        break;
    case 7:
        str = "9 of ";
        break;
    case 8:
        str = "10 of ";
        break;
    case 9:
        str = "J of ";
        break;
    case 10:
        str = "Q of ";
        break;
    case 11:
        str = "K of ";
        break;
    case 12:
        str = "A of ";
        break;
    }


    // remainder of 0 indicates clubs
    // remainder of 1 indicates diamonds
    // remainder of 2 indicates hearts
    // remainder of 3 indicates spades
    switch (card_raw % 4)
    {
    case 0:
        str += "clubs";
        break;
    case 1:
        str += "diamonds";
        break;
    case 2:
        str += "hearts";
        break;
    case 3:
        str += "spades";
        break;
    }
    return str;
}
