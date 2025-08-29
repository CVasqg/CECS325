//Deck.cpp

// Citlally Vasquez
// Class (CECS 325-01)
// Prog 1 – Counting Letters
// 02/14/24
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <cstdlib> 
#include <ctime> 
#include <vector> 

using namespace std;

// Creates a deck of 52 cards
Deck::Deck() {
    char suits[] = {'C', 'D', 'H', 'S'};
    char ranks[] = {'A','2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 13; ++j) {
            cards.push_back(Card(ranks[j], suits[i]));
        }
    }
}


// Deals a card
Card Deck::deal() {
    if (!cards.empty()) {
        Card dealtCard = cards.back();  // Get the last card from the deck
        cards.pop_back();               // Remove the last card from the deck
        return dealtCard;
    } else {
        cerr << "No cards left in the deck!" << endl;
        return Card('\0', '\0');        // Return an empty card
    }
}

// Show all the cards in the deck
void Deck::display() {
    for (size_t i = 0; i < cards.size(); ++i) {
        cards[i].display();
        cout << " ";
    }
    cout << endl;
}

// Shuffles the cards in the deck
void Deck::shuffle() {
    srand(static_cast<unsigned int>(time(nullptr))); 

    int n = cards.size();
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % 52;  // Generate a random index in [0, 51]
        
        // Swap card at index i with card at index j
        swap(cards[i], cards[j]);
    }
}

