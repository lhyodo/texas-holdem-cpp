#ifndef GETRANK
#define GETRANK

#include <stdio.h>
#include <iostream>
// ===================== NOTE =====================
// Deck is organized from 2 of clubs at index 0 and ace of spades at index 51
// Order of suits is alphabetical. clubs, diamonds, hearts, spades
// Rank of a card is obtained by the formula card_raw/4, as defined in GetRank.cpp
// A "Jack" card has a rank of 9
// A    "2" card has a rank of 0
// An "Ace" card has a rank of 12

// Suit of a card is obtained by the formula card_raw%4, as defined in GetSuit.cpp
// A "Spades" card has a suit of 3
// A  "Clubs" card has a suit of 0
int GetRank(int card_raw)
{
    return (card_raw / 4);
}
#endif