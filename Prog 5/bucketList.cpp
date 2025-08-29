// Citlally Vasquez
// CECS 325-01
//  Prog 5 - Bucketlist (vectors)
//  Due (04/22/24)
//
//  I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

// Initiates global variable to count swaps
int globalSwapCount = 0;

// Bucket class
class Bucket {
private:
    vector<int> v;

public:
    Bucket();
    void generate(int size, int min, int max);
    void sort(); // Bubble sort
    int size();
    int atIndex(int index);
    int merge(Bucket b); // Merges sort
};

Bucket::Bucket() {}

// Function from Bucket class to generate random numbers and fill bucket
void Bucket::generate(int size, int min, int max) {
    for (int i = 0; i < size; i++) {
        int randomNum = min + rand() % (max - min + 1); // Generates a random number between min and max
        v.push_back(randomNum); // Adds a random number to the bucket
    }
}

// Function from Bucket class to sort the numbers in the bucket using Bubble Sort
void Bucket::sort() {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]); // Swaps the elements if they are not in right order
                globalSwapCount++; // Global swap count increments each time
            }
        }
    }
}

// Function from Bucket class returns the size of the bucket
int Bucket::size() {
    return v.size();
}

// Function from Bucket class accesses an element at a certain index in the bucket
int Bucket::atIndex(int index) {
    return v[index];
}

// Function from Bucket class merges another bucket into this bucket
int Bucket::merge(Bucket b) {
    for (int i = 0; i < b.size(); i++) {
        v.push_back(b.atIndex(i)); // Adds each element from the other bucket to this bucket
    }
    return 0;
}

// Main function
int main(int argc, char *argv[]) {
    srand(time(0));

    if (argc != 5) {
        cout << "Usage: bucketList <bucketCount> <bucketSize> <min> <max>" << endl; // Indicates bucket's count, size, and it's min/max
        return 1;
    }

    int bucketCount = stoi(argv[1]);
    int bucketSize = stoi(argv[2]);
    int bucketMin = stoi(argv[3]);
    int bucketMax = stoi(argv[4]);

    // Outputs bucket stats
    cout << "Bucket Count: " << bucketCount << endl;
    cout << "Bucket Size: " << bucketSize << endl;
    cout << "Bucket Min Value: " << bucketMin << endl;
    cout << "Bucket Max value: " << bucketMax << endl;

    vector<Bucket> list; // Creates a vector to store buckets
    Bucket *bptr;

    // Generates and fills bucket
    for (int i = 0; i < bucketCount; i++) {
        bptr = new Bucket;
        bptr->generate(bucketSize, bucketMin, bucketMax);
        list.push_back(*bptr); // Add the generated bucket to the list
    }

    // Sorts each bucket
    for (vector<Bucket>::iterator it = list.begin(); it != list.end(); it++) {
        it->sort();
    }

    Bucket endGame;

    // Merge all buckets into one bucket
    while (!list.empty()) {
        endGame.merge(list[0]);
        list.erase(list.begin());
    }

    // Write the merged bucket to a file called "bucketlist.out"
    fstream out("bucketList.out", ios::out);
    for (int i = 0; i < endGame.size(); i++)
        out << endGame.atIndex(i) << endl;
    cout << "Global Swap Count: " << globalSwapCount << endl;
    cout << "\nbucketList.out has " << bucketCount * bucketSize << " sorted numbers\n";

    return 0;
}
