// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
 
bool checkJoltJumps(int* input, const int k_size);
int countJoltJumps(int* input, const int k_size, const int jump);

void load_x(int* input, const int index, int* buffer, const int x);
bool check3(int* buffer);
bool check4(int* buffer);
void part2 (int* input, const int k_size);
void buildTree(int* input, const int k_size, int pos, long long unsigned &validPaths, int* output);

int main()
{
	const int k_size = 11; //31; //107 array Length
	std::FILE* f_inFile = std::fopen("test.txt", "r");
	
	int input [k_size];
	int output [k_size];


	for (int i = 0; i < k_size; i++)
	{
		fscanf(f_inFile, "%d", &(input[i]));
		// std::cout << "output: " << instruction[i] << " " << instrVal[i] << "\n";
	}
	
	std::cout << "Read Complete\n";



	// std::cout << "Input: " << input[0] << "\n";
	// std::cout << "Input: " << input[1] << "\n";
	// std::cout << "Input: " << input[2] << "\n";
	// std::cout << "Input: " << input[3] << "\n";
 	// std::cout << "\n\n\n";

	std::sort(input, input+k_size);
	bool passed = checkJoltJumps(input, k_size);
	std::cout << "Jolt Pass: " << passed << "\n";
	
	int jump1 = countJoltJumps(input, k_size, 1);
	int jump2 = countJoltJumps(input, k_size, 2);
	int jump3 = countJoltJumps(input, k_size, 3);

	std::cout << "1 jumps: " << jump1 << "\n";
	std::cout << "2 jumps: " << jump2 << "\n";
	std::cout << "3 jumps: " << jump3 << "\n";
	std::cout << "Part 1 Result: " << jump1 * jump3 << "\n";

	// Part 2
	std::cout << "\n\nPart 2  ";

	std::cout <<"input: \n";
	for(int i = 0; i < k_size; i++){std::cout << input[i] << "\n";}
	std::cout <<"\ntree outputs \n";

	long long unsigned validPaths = 1;
	int pos = 0;
	buildTree(input, k_size, pos, validPaths, output);
	
	std::cout << "Valid Paths: " << validPaths << "\n";



	// std::cout << "Input: " << input[0] << "\n";
	// std::cout << "Input: " << input[1] << "\n";
 	// std::cout << "Input: " << input[2] << "\n";
	// std::cout << "Input: " << input[3] << "\n";
	std::cout << "\n\n\n";
	return 0;

}

int countJoltJumps(int* input, const int k_size, const int jump)
{
	int count = 0;

	const int dif = input[0];
	if(dif == jump)
	{
		count++;
	}
	if(jump == 3)
	{
		count++;
	}

	for(int i = 0; i < k_size-1; i++)
	{
		const int dif = input[i+1]-input[i];
		if (dif == jump)
		{
			count++;
		}
	}

	return count;
}

//// Assumptions
// No more than 2 Adapters can be removed in a row
// will need to record 


void load_x(int* input, const int index, int* buffer, const int x)
{
	for(int i = 0; i < x; i++)
	{
		buffer[i] = input[index+i];
	}
}

bool check3(int* buffer)
{
	bool out = (buffer[2] - buffer[0]) <= 3;
	return out;
}

bool check4(int* buffer)
{
	bool out = (buffer[3] - buffer[0]) <= 3;
	return out;
}

void part2 (int* input, const int k_size)
{
	int buffer_3 [3]; // check gaps of 1
	int buffer_4 [4]; // check gaps of 2

	load_x(input, 0, buffer_3, 3);
	load_x(input, 0, buffer_4, 4);

	std::cout << "buffer 3: " << check3(buffer_3) << "\n";
	std::cout << "buffer 4: " << check4(buffer_4) << "\n";
}

// input 		- the array of adapters 
// k_size 		- the total length of input array
// pos 			- position in the input array
// validPaths	- number of valid paths (long long!)
void buildTree(int* input, const int k_size, int pos, long long unsigned &validPaths, int* output)
{
	//  search for 3 then 4
	// std::cout << input[pos] << " ";
	int currentPos = pos; // debug

	int buffer_3[3];
	for (int i = pos; i < k_size-3; i++)
	{
		load_x(input, i, buffer_3, 3);
		const bool valid = check3(buffer_3);
		if(valid)
		{	// valid gap of 1!
			int nextPos = i+2; // move position to after gap

			for(int j = currentPos; j < i; j++)
			{	// for debugging
				std::cout << input[j] << " ";
			}

			validPaths++;
			buildTree(input, k_size, nextPos, validPaths, output);
		}
	}
	
	//// When finished will gaps of 1
	// search for gaps of 2
	int buffer_4[4];
	for (int i = pos; i < k_size-4; i++)
	{
		load_x(input, i, buffer_4, 4);
		const bool valid = check4(buffer_4);
		if(valid)
		{	// valid gap of 1!
			int nextPos = i+3; // move position to after gap

			for(int j = currentPos; j < pos; j++)
			{	// for debugging
				std::cout << input[j] << " ";
			}

			validPaths++;
			buildTree(input, k_size, nextPos, validPaths, output);
		}
	}
	
	std::cout <<"\n";
	// check for 3
		// load current position buffer
		// search remaining input for single gaps
			// if found valid gap
				// increase index for after gap
				// Increment counter
					// search line again
	
	// if cant find a 3 gap 
	// check for 4
		// load current position buffer
		// search reamain input for second gaps
			// if found valid gap
				// increase index for after gap
				// Increment counter
					// search line again
}

bool checkJoltJumps(int* input, const int k_size)
{	// check that each jump isnt greater than 3!
	// return true if correct jumps
	const int k_maxJump = 3;

	for(int i = 0; i < k_size-1; i++)
	{
		const int dif = input[i+1]-input[i];
		if(dif > 3)
		{
			return false;
		}
	}

	return true;
}
