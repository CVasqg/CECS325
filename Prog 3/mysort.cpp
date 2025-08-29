// Citlally Vasquez
// CECS 325-01
//  Prog 3 - Bubblesort
//  Due (03/11/24)
//
//  I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream> //allows files to be created, read, and written into
#include <cstdlib>
#include <ctime>
using namespace std;

 // Calls bubblesort from main
void bubblesort(int a[], int length);

// argv is an array of char string
int main(int argc, char *argv[]) 
{
	// checks if 3 parameters are present
    if (argc != 3) 
    {
        cout << "Please enter 3 parameters:\n";
        cout << "    Parameter 1: total count of numbers you want.\n";
        cout << "    Parameter 2: min value.\n";
        exit(EXIT_SUCCESS);
    }

	// xFile = numbers.dat
	ifstream xFile(argv[1]);  
	ofstream output(argv[2]);
		
	// Creates large array
    int a[1000000]; 
    int len = 0;
    int num = 0;

	while (xFile >> num)
	{
		a[len++] = num;
	}
	
	//calls bubblesort function
    bubblesort(a, len); 

    // Prints sorted array
    for (int i = 0; i < len; i++) 
    {
        output << a[i] << endl;
    }

	//closes files
	xFile.close(); 
	output.close();
    return 0;
}

//Bubblesort function
void bubblesort(int a[], int length)
{
    bool swapped;
    int i = 0;
    do
    {
        swapped = false;
        for (int j = 0; j < length - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = true;
            }
        }
        i++;
    } while (swapped);
}
