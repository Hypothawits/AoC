#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <bitset>
#include <chrono>
// #define k_width 10//92
// #define k_size 10//91
// #define k_size 7
using namespace std;

#include "Header.h""

constexpr bool debug = false;

int isLarger(const int x, const int y)
{	// is X larger than Y?
	return (x > y);
}


int main()
{
	// ----------------------------------------
	// Read input text file
	std::ifstream f_inFile;
	if (debug)
	{
		f_inFile.open("test.txt");
	}
	else 
	{
		f_inFile.open("input.txt");
	}
	
	

	vector<int> input;
	int in;
	while (f_inFile >> in)
	{
		input.push_back(in);
	}

	// ----------------------------------------
	int count = 0;
	for (int i = 1; i < input.size(); i++)
	{
		const int y = input[i - 1];
		const int x = input[i];

		count += isLarger(x, y);
	}


	cout << "Part 1: " << count << endl;

	int count_2 = 0;
	for (int i = 3; i < input.size(); i++)
	{
		
		const int a = input[(i-1) - 2];
		const int b = input[(i-1) - 1];
		const int c = input[(i-1)];

		const int A = a + b + c;

		const int x = input[i - 2];
		const int y = input[i - 1];
		const int z = input[i];

		const int B = x + y + z;

		count_2 += isLarger(B, A);
	}

	cout << "Part 2: " << count << endl;
}