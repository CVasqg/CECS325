// Citlally Vasquez
// CECS 325-01 Prog 0
// Due 01/31/24

#include <iostream>
using namespace std;

int fibo(int n) // Fibo function
{
	if (n == 1 || n == 0) // if n is equal to one or zero, then it will return as an error. If it's not then it must go through the calculations below
		return 1;
	else
		return fibo(n-1) + fibo(n-2); // (RECURSION)
}

int main() // Main function
{
	for (int i = 0; i <= 20; i++) // For every # between zero and twenty that is a fibo #.
		cout << i << ":" << fibo(i) <<endl; // Prints i and fibo #.

	return 0; // "return 0" indicates that program will output without errors.
}

// Do while forces you to go through the loop once no matter the condition
// while goes through the loop if condition is met beforehand

// "endl" = "\n" in python

// use "./_(filename)_" in terminal to run the current file in folder