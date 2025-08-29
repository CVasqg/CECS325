// Deck.h

// Citlally Vasquez
// Class (CECS 325-01)
// Prog 1 – Counting Letters
// 02/14/24
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#ifndef DECK_H
#define DECK_H
#include <vector>
#include "Card.h"
#include <iostream>
using namespace std;

class Deck {
public:
    Deck();             // constructor which creates a deck of 52 cards
    Card deal();        // deal a card
    void display();     // show all the cards in the deck
    void shuffle();     // shuffle the cards in the deck

private:
    vector<Card> cards; // vector to hold the deck of cards
};

#endif // DECK_H
