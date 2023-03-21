#include <stdio.h>
#include <iostream>

int GetSuit(int card_raw)
{
    return (card_raw % 4);
}