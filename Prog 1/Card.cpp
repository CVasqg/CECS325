//Card.cpp

// Citlally Vasquez
// Class (CECS 325-01)
// Prog 1 – Counting Letters
// 02/14/24
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include "Card.h"
#include <iostream>

using namespace std;

// Creates a card and sets the suit and rank
Card::Card(char rank, char suit) : rank(rank), suit(suit) {}

// Displays the card
void Card::display() {
    cout << rank << suit;
}

int Card::compare(Card otherCard) {
    if (rank == otherCard.rank && suit == otherCard.suit) { // Checks if cards are of the same rank and suit, tie
        return 0; 
    } else if (rank == 'A' || (otherCard.rank != 'A' && rank > otherCard.rank)) {
        return 1; // Current card wins
    } else {
        return -1; // Current card loses
    }
}
