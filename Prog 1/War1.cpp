// Citlally Vasquez
// Class (CECS 325-01)
// Prog 1 – One Card WAR
// 02/14/24
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <string>
#include <vector>
#include "Card.h"
#include "Deck.h"

using namespace std;

int main() {
    //Create a new deck
    Deck deck;

    //Ask for player names
    string player1Name, player2Name;
    cout << "Enter the name of the first player: ";
    cin >> player1Name;
    cout << "Enter the name of the second player: ";
    cin >> player2Name;
 

    //Displays unshuffled deck
    cout << "Original Deck" << endl;
    deck.display();
    cout << endl;

    //Shuffles the deck
    deck.shuffle();

    //Displays shuffled deck
    cout << "Shuffled Deck" << endl;
    deck.display();
    cout << endl;

    //26 games are played
    int player1Wins = 0, player2Wins = 0, ties = 0;

    for (int i = 0; i < 26; ++i) {
        cout << "Game " << i + 1 << endl;
        cout << "--------" << endl;

        Card card1 = deck.deal();
        Card card2 = deck.deal();

        cout << player1Name << " => ";
        card1.display();
        cout << endl;
        cout << player2Name << " => ";
        card2.display();
        cout << endl;

        if (card1.compare(card2) == 1) {
            cout << player1Name << " => Winner" << endl;
            player1Wins++;
        } else if (card1.compare(card2) == -1) {
            cout << player2Name << " => Winner" << endl;
            player2Wins++;
        } else {
            cout << "Tie" << endl;
            ties++;
        }

        cout << endl;
    }

    // Final game Stats
    cout << "------Final Stats-------" << endl;
    cout << player1Name << " vs. " << player2Name << endl;
    cout << "Wins: " << player1Wins << " " << player2Wins << endl;
    cout << "Losses: " << 26 - player1Wins - ties << " " << 26 - player2Wins - ties << endl;
    cout << "Ties: " << ties << " " << ties << endl;

    return 0;
}

