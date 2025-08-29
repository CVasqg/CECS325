// Citlally Vasquez
// CECS 325-01
//  Prog 4 - Sorting Contest using pthreads
//  Due (03/25/24)
//
//  I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <pthread.h>
using namespace std;

// Sets limit for array "numbers"
const int MAX_ARRAY_SIZE = 1000000;
// 8 threads
const int NUM_THREADS = 8; 
// Array is created to hold up to 1 million numbers
int numbers[MAX_ARRAY_SIZE]; 

// Structure to pass parameters to the sorting function
struct ThreadData {
    int* array;
    int length;
};

// Bubblesort function
void bubblesort(int a[], int length) {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < length - 1; i++) {
            if (a[i] > a[i + 1]) {
                // Swap elements
                int temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped);
}

// Merges two subarrays of array[].
void merge(int arr[], int l, int m, int r) { // First subarray is array[l..m] | Second subarray is array[m+1..r]
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Creates temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l - r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
// Mergesort function
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Sorting function to be called by each thread. Uses both bubblesort and mergesort
void* sort_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    if (data->length <= 10000) {
        bubblesort(data->array, data->length); // Calls in bubblesort
    } else {
        mergeSort(data->array, 0, data->length - 1); // Calls in mergesort
    }
    pthread_exit(NULL);
}

// MAIN
int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Enter 2 Parameters:\n";
        cout << "     Parameter 1: input file.\n";
        cout << "     Parameter 2: output file.\n";
        exit(EXIT_FAILURE);
    }

    string inputFile = argv[1];
    string outputFile = argv[2];
    ifstream input(inputFile);
    ofstream out(outputFile);
    int position = 0;
    int number;

    while (input >> number && position < MAX_ARRAY_SIZE) {
        numbers[position++] = number;
    }
    input.close();

    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];
    int sectionSize = position / NUM_THREADS;

    // Create threads to sort each section of the array
    for (int i = 0; i < NUM_THREADS; ++i) {
        threadData[i].array = &numbers[i * sectionSize];
        threadData[i].length = (i == NUM_THREADS - 1) ? (position - (NUM_THREADS - 1) * sectionSize) : sectionSize;
        pthread_create(&threads[i], NULL, sort_thread, (void*)&threadData[i]);
    }

    // Wait for all threads to finish using for loop instead of writing each pthread out
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Merge sorted sections using for loop instead of writing each pthread out
    for (int i = 1; i < NUM_THREADS; ++i) {
        merge(numbers, 0, sectionSize * i - 1, sectionSize * (i + 1) - 1);
    }

    // Print sorted array to output file
    for (int i = 0; i < position; i++) {
        out << numbers[i] << endl;
    }
    out.close();

    return 0;
}
