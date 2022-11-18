// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
using namespace std;
 

bool isNumber(char in)
{
	switch (in)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return 1;
		break;
	
	default:
		//NAN
		return 0;
		break;
	}
}

bool isItMadeOfBuffer(long long* buffer, long long x);

void fillBuffer(long long* buffer, long long* input, int offset);

int main()
{
	const int k_size = 1000; //623 array Length
	// std::string input[k_size];

    // std::ifstream f_inFile;
	// f_inFile.open("input.txt", ios::in);

	std::FILE* f_inFile = std::fopen("input.txt", "r");
	
	long long input [k_size];


	for (int i = 0; i < k_size; i++)
	{
		fscanf(f_inFile, "%lld", &(input[i]));
		// std::cout << "output: " << instruction[i] << " " << instrVal[i] << "\n";
	}
	
	std::cout << "Read Complete\n";

	long long buffer [25];

	// load in first 25
	long long int invalid = 393911906;
	for (int i = 1; i < k_size; i++)
	{
		fillBuffer(buffer, input, i);
		long long nextValue = input[i+25];
		bool wasIt = isItMadeOfBuffer(buffer, nextValue);

		// std::cout << i << " - " << nextValue << "\n";
		if(!wasIt)
		{
			// std::cout << "Found it!" << nextValue << "\n";
			invalid = nextValue;
			break;
		}
	}
	std::cout << "invalid: " << invalid << "\n";

	long long total = 0;
	for(int offset = 0; offset < k_size; offset++)
	{
		total = 0;
		for(int i = 0; i < k_size; i++)
		{
			total += input[offset + i];
			// std::cout << total << "\n";
			if(total == invalid)
			{
				//found the array
				std::cout << "offset: " << offset << "\n";
			}
			if (total > invalid)
			{
				break;
			}
			
		}
	}
	

	long long smallest = INT64_MAX;
	long long largest  = 0;

	std::cout << "get buffer of Invalid Sum" << "\n";
	fillBuffer(buffer, input, 517);

	for (int i = 0; i < 25; i++)
	{	
		if(buffer[i] > largest){largest = buffer[i];}
		if(buffer[i] < smallest){smallest = buffer[i];}		
	}
	// 20819286924486 to large
	std::cout << "Result: " << smallest << "+" << largest << "\n";
	std::cout << "Result: " << smallest + largest << "\n";
 	std::cout << "\n\n\n";
	return 0;

}

void fillBuffer(long long* buffer, long long* input, int offset)
{
	// std::cout << "offset: " << offset << "\n";
	for(int i = 0; i < 25; i++)
	{
		buffer[i] = input[offset+i];
	}
}

bool isItMadeOfBuffer(long long* buffer, long long x)
{ // Can x be made from two values in Buffer
	bool found = false;

	for(int i = 0; i < 25; i++)
	{
		long long bufValue = buffer[i];

		// search val must be possitive
		// long long searchVal = (bufValue > x) ? (bufValue-x):(x-bufValue);
		long long searchVal = (x-bufValue);

		// search for searchVal in list
		for(int j = 0; j < 25; j++)
		{
			if(searchVal > 0)
			{
				// std::cout << "search val: " << searchVal << " -- buffer val: " << buffer[j] << "\n";
				if(searchVal == buffer[j])
				{	// x = bufValue + searchVal
					// std::cout << "x: " << x <<  " = val 1: " << bufValue << " +  val 2: " << searchVal << "\n";
					found = true;
				}
			}
		}
		
	}
	
	return found;
}
