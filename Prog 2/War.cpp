// Citlally Vasquez
// Class (CECS 325-01)
// Prog 2 – One Card WAR
// 02/26/24
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Class Card
class Card {
private:
    char suit;
    char rank;

public:
    Card() {}
    Card(char s, char r) : suit(s), rank(r) {}

    // Displays card
    void display() {
        // Displays char "T" as "10"
        if (rank == 'T') {
            cout << "10";
        } else {
            cout << rank;
        }
        cout << suit << " ";
    }

    // Compares cards
    int compare(Card other) {
        if (rank > other.rank)
            return 1;
        else if (rank == other.rank)
            return 0;
        else
            return -1;
    }
};

// Class Deck
class Deck {
private:
    // Array of 52 card deck
    static const int totalCards = 52;
    Card cards[totalCards];
    int currentCardIndex;

public:
    Deck() : currentCardIndex(0) {
        char suits[] = {'C', 'S', 'D', 'H'};
        char ranks[] = {'A','2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

        int index = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 13; ++j) {
                cards[index++] = Card(suits[i], ranks[j]);
            }
        }
    }

    // Deals card from deck
    Card deal() {
        if (isEmpty()) {
            throw "Deck is empty";
        }
        // Informs player that deck is empty
        if (currentCardIndex >= totalCards) {
            throw "Deck is empty";
        }
        return cards[currentCardIndex++];
    }

    // Shuffles card
    void shuffle() {
        srand(time(0));
        for (int i = totalCards - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(cards[i], cards[j]);
        }
    }

    bool isEmpty() {
        return currentCardIndex == totalCards;
    }

    // Displays card
    void display() {
        for (int i = 0; i < totalCards; ++i) {
            cards[i].display();
        }
        cout << endl;
    }
};

int main() {
    // Initializes deck
    Deck deck;

    // Ask for Players' names
    string player1, player2;
    cout << "Enter the name of the first player: ";
    cin >> player1;
    cout << "Enter the name of the second player: ";
    cin >> player2;

    // Ask how many games will be played
    int numGames;
    cout << "How many games will they play? ";
    cin >> numGames;

    // Displays unshuffled deck
    cout << "Original Deck" << endl;
    deck.display();
    cout << endl;

    // Shuffles the deck
    deck.shuffle();

    // Displays shuffled deck
    cout << "Shuffled Deck" << endl;
    deck.display();
    cout << endl;

    int player1Wins = 0, player2Wins = 0, ties = 0;

    try {
        for (int i = 0; i < numGames; ++i) {
            cout << "Game " << (i + 1) << endl;
            cout << "--------" << endl;

            // Deals player's card
            Card player1Card = deck.deal();
            Card player2Card = deck.deal();

            // Display player 1 card
            cout << player1 << "=> ";
            player1Card.display();
            cout << endl;

            // Display player 2 card
            cout << player2 << "=> ";
            player2Card.display();
            cout << endl;

            // Compares player 1 and player 2 cards and declares win or tie
            int result = player1Card.compare(player2Card);
            if (result == 1) {
                cout << player1 << " wins!" << endl;
                player1Wins++;
            } else if (result == -1) {
                cout << player2 << " wins!" << endl;
                player2Wins++;
            } else {
                cout << "Tie game" << endl;
                ties++;
            }

            cout << endl;
        }
        // Error is displayed along with empty deck
    } catch (const char* msg) {
        cerr << "Error - " << msg << endl;
    }

    // Final statisitics of game
    cout << "------Final Stats-------" << endl;
    cout << player1 << " vs. " << player2 << endl;
    cout << "Wins: " << player1Wins << " " << player2Wins << endl;
    cout << "Losses: " << player2Wins << " " << player1Wins << endl;
    cout << "Ties: " << ties << " " << ties << endl;

    return 0;
}
