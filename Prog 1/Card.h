//Card.h
// Citlally Vasquez
// Class (CECS 325-01)
// Prog 1 – Counting Letters
// 02/14/24
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>
using namespace std;

class Card 
{
public:
    Card(char rank, char suit); // constructor to create a card, setting the suit and rank
    void display();             // display the card example: AC, 10S, KD
    int compare(Card otherCard); // return 1 for win, 0 for tie, -1 for lose

private:
    char rank; // rank of the card 
    char suit; // suit of the card 
};

#endif // CARD_H
