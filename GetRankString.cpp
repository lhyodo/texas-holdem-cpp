
#include <iostream>
#include <string>

std::string GetRankString(int card_rank)
{
    switch (card_rank)
    {
    case 0:
        return "2";
        break;
    case 1:
        return "3";
        break;
    case 2:
        return "4";
        break;
    case 3:
        return "5";
        break;
    case 4:
        return "6";
        break;
    case 5:
        return "7";
        break;
    case 6:
        return "8";
        break;
    case 7:
        return "9";
        break;
    case 8:
        return "10";
        break;
    case 9:
        return "Jack";
        break;
    case 10:
        return "Queen";
        break;
    case 11:
        return "King";
        break;
    case 12:
        return "Ace";
        break;
    }
}
