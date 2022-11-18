// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
// #define k_size 11
#define k_size 107 //31

using namespace std;
 
bool checkJoltJumps(int* input);
int countJoltJumps(int* input, const int jump);

void load_x(int* input, const int index, int* buffer, const int x);
bool check3(int* buffer);
bool check4(int* buffer);
void buildTree(int* input, int pos, long long unsigned &validPaths, int* output);

int main()
{
	std::FILE* f_inFile = std::fopen("input.txt", "r");
	
	// int input [k_size];
	int input [k_size+1]; 	//part two
	input[k_size] = 0; 		// part two
	int output [k_size];


	for (int i = 0; i < k_size; i++)
	{
		fscanf(f_inFile, "%d", &(input[i]));
		// std::cout << "output: " << instruction[i] << " " << instrVal[i] << "\n";
	}
	
	std::cout << "Read Complete\n";

	// std::sort(input, input+k_size);
	std::sort(input, input+k_size+1); // part 2
	bool passed = checkJoltJumps(input);
	std::cout << "Jolt Pass: " << passed << "\n";
	
	int jump1 = countJoltJumps(input, 1);
	int jump2 = countJoltJumps(input, 2);
	int jump3 = countJoltJumps(input, 3);

	std::cout << "1 jumps: " << jump1 << "\n";
	std::cout << "2 jumps: " << jump2 << "\n";
	std::cout << "3 jumps: " << jump3 << "\n";
	std::cout << "Part 1 Result: " << jump1 * jump3 << "\n";

	// Part 2
	std::cout << "\n\nPart 2  ";

	std::cout <<"input: \n";
	for(int i = 0; i < 8+1; i++){std::cout << input[i] << "\n";}
	std::cout <<"\ntree outputs \n";

	int jump2_1s_inRow = 0; // number of 2 1 jolt jumps in a row
	int jump3_1s_inRow = 0; // number of 3 1 jolt jumps in a row
	int jump4_1s_inRow = 0; // number of 4 1 jolt jumps in a row

	// jump = input[pos+1]-input[pos];	

	int pos = 0;
	while(pos < k_size+1) // +1 for part two with 0 added
	{
		int jumpCount = 0;
		int jump = input[pos+1]-input[pos];
		while (jump == 1)
		{
			pos++;
			jumpCount++;
			jump = input[pos+1]-input[pos];
		}
		if(jumpCount == 2){jump2_1s_inRow++;};
		if(jumpCount == 3){jump3_1s_inRow++;};
		if(jumpCount == 4){jump4_1s_inRow++;};
		pos++;
	}

	std::cout << "Jump 2rows count : " << jump2_1s_inRow << "\n";
	std::cout << "Jump 3rows count : " << jump3_1s_inRow << "\n";
	std::cout << "Jump 4rows count : " << jump4_1s_inRow << "\n";

	std::cout << std::pow(2, jump2_1s_inRow) << "\n";
	std::cout << std::pow(4, jump3_1s_inRow) << "\n";
	std::cout << std::pow(7, jump4_1s_inRow) << "\n";
	long long unsigned result = std::pow(2, jump2_1s_inRow) * std::pow(4, jump3_1s_inRow) * std::pow(7, jump4_1s_inRow);

	std::cout << "Result: " << std::pow(2, jump2_1s_inRow) * std::pow(4, jump3_1s_inRow) * std::pow(7, jump4_1s_inRow) << "\n";
	printf ("Result: %lld\n", result);

	std::cout << "\n\n\n";
	return 0;

}





int countJoltJumps(int* input, const int jump)
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

// input 		- the array of adapters 
// k_size 		- the total length of input array
// pos 			- position in the input array
// validPaths	- number of valid paths (long long!)

void buildTree(int* input, int pos, long long unsigned &validPaths, int* output)
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
			buildTree(input, nextPos, validPaths, output);
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
			buildTree(input, nextPos, validPaths, output);
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

bool checkJoltJumps(int* input)
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
