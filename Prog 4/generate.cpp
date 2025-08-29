// Citlally Vasquez
// CECS 325-01
//  Prog 4 - Sorting Contest using pthreads
//  Due (03/25/24)
//
//  I certify that this program is my own original work. I did not copy any part of this program from any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream> //file library
using namespace std;

// Main generate function
int main(int argc, char *argv[])
{
  if (argc < 4) //Checks for 3 parameters
  {
      cout << "Please enter 3 parameters:\n";
      cout << "    Parameter 1: total count of numbers you want.\n";
      cout << "    Parameter 2: min value.\n";
      cout << "Example: %generate 10000000 100000 999999\n";
      exit(EXIT_SUCCESS);
  }

  for (int i=0; i<argc; i++)
  {
    cout << "argv[" <<i<<"]:"<<argv[i]<<endl;
  }
  int COUNT = stoi (argv[1]);
  int MIN = stoi(argv[2]);
  int MAX = stoi(argv[3]);

  ofstream fout;
  fout.open("numbers.dat", ios::out); // Opens numbers.dat file
  for (int i = 0; i < COUNT; i++)
  {
    fout << (rand() % (MAX-MIN+1) + MIN) <<endl;
  }
  fout.close();
  return 0;
  
}
