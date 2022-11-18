// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
// #define k_width 10//92
// #define k_size 10//91
#define k_width 92
#define k_size 91
using namespace std;

char applyRules(int pos_x, int pos_y, char* input);

int coord(int pos_x, int pos_y)
{
	//[y][x]
	// int k_size = 91; 
	// int k_width = 92;
	return ((1 + (k_width + 2)) + (k_width + 2) * pos_y + pos_x);
}

void printArray(char* in, int x, int y)
{
	// int k_width = 92+2;
	for (int i = 0; i < 5; i++)//y+2; i++)
	{
		for (int j = 0; j < x + 2; j++)
		{
			std::cout << in[(k_width + 2) * i + j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

bool isSame(char* x, char* y)
{
	for (int i = 0; i < (k_size + 2) * (k_width + 2); i++)
	{
		if (x[i] != y[i])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	// const int k_size = 91;
	// const int k_width = 92; // 10
	// std::FILE* f_inFile = std::fopen("test.txt", "r");

	char input[(k_size + 2) * (k_width + 2)]; // [y][x]
	char next[(k_size + 2) * (k_width + 2)]; // The next board

	for (int i = 0; i < (k_size + 2) * (k_width + 2); i++)
	{
		input[i] = '.';
		next[i] = '.';
	}

	std::ifstream f_inFile;
	f_inFile.open("input.txt", ios::in);
	// f_inFile.open("test.txt", ios::in);

	for (int i = 0; i < k_size; i++)
	{
		std::string in;
		getline(f_inFile, in);
		for (int j = 0; j < k_width; j++)
		{
			input[coord(j, i)] = in[j];
		}

	}


	printArray(input, k_width, k_size);

	std::cout << "Read Complete\n";
	// std::exit(0);
	std::cout << "Apply Rules\n";

	bool stable = false;
	int cyclesCount = 0;
	while (!stable)
	{

		if (cyclesCount % 100)
		{
			std::cout << cyclesCount << "\n";
		}

		for (int pos_x = 0; pos_x < k_width; pos_x++)
		{
			for (int pos_y = 0; pos_y < k_size; pos_y++)
			{
				next[coord(pos_x, pos_y)] = applyRules(pos_x, pos_y, input);
			}
		}
		stable = isSame(input, next);

		if (!stable)
		{
			for (int pos_x = 0; pos_x < k_width; pos_x++)
			{
				for (int pos_y = 0; pos_y < k_size; pos_y++)
				{
					input[coord(pos_x, pos_y)] = applyRules(pos_x, pos_y, next);
				}
			}
			stable = isSame(input, next);
		}

	}

	std::cout << "Final Stable Config found in: " << cyclesCount << "\n";
	printArray(next, k_width, k_size);

	std::cout << "Counting full seats\n";
	int result = 0;
	for (int pos_x = 0; pos_x < k_width; pos_x++)
	{
		for (int pos_y = 0; pos_y < k_size; pos_y++)
		{
			if (input[coord(pos_x, pos_y)] == '#') { result++; };
		}
	}

	std::cout << "Number of Full Seats:" << result << "\n";


	std::cout << "\n\n\n";
	return 0;
	// 2129 is too low
}







char isEmpty(char in)
{
	if (in == '.') { return 1; }
	if (in == 'L') { return 1; }
	return 0;
}

bool ruleOne(char* input, int pos_x, int pos_y)
{
	// true if all chairs empty, then full chair
	// false if some chairs are full, then leave chair
	if (!isEmpty(input[coord(pos_x - 1, pos_y + 1)])) { return false; }
	if (!isEmpty(input[coord(pos_x - 1, pos_y + 0)])) { return false; }
	if (!isEmpty(input[coord(pos_x - 1, pos_y - 1)])) { return false; }
	if (!isEmpty(input[coord(pos_x + 0, pos_y + 1)])) { return false; }
	if (!isEmpty(input[coord(pos_x + 0, pos_y - 1)])) { return false; }
	if (!isEmpty(input[coord(pos_x + 1, pos_y + 1)])) { return false; }
	if (!isEmpty(input[coord(pos_x + 1, pos_y + 0)])) { return false; }
	if (!isEmpty(input[coord(pos_x + 1, pos_y - 1)])) { return false; }
	return true;
}

char howManyEmpty(char* input, int pos_x, int pos_y)
{
	const char TL = isEmpty(input[coord(pos_x - 1, pos_y + 1)]); //(pos_y +1) + (pos_x -1)] );
	const char L = isEmpty(input[coord(pos_x - 1, pos_y + 0)]); //(pos_y +0) + (pos_x -1)] );
	const char BL = isEmpty(input[coord(pos_x - 1, pos_y - 1)]); //(pos_y -1) + (pos_x -1)] );
	const char T = isEmpty(input[coord(pos_x + 0, pos_y + 1)]); //(pos_y +1) + (pos_x +0)] );
	const char B = isEmpty(input[coord(pos_x + 0, pos_y - 1)]); //(pos_y -1) + (pos_x +0)] );
	const char TR = isEmpty(input[coord(pos_x + 1, pos_y + 1)]); //(pos_y +1) + (pos_x +1)] );
	const char R = isEmpty(input[coord(pos_x + 1, pos_y + 0)]); //(pos_y +0) + (pos_x +1)] );
	const char BR = isEmpty(input[coord(pos_x + 1, pos_y - 1)]); //(pos_y -1) + (pos_x +1)] );

	return (TL + L + BL + T + B + TR + R + BR); // return how many empty seats
	// 8 = all empty

}
char howManyFull(char* input, int pos_x, int pos_y)
{
	const char k_max_seats = 8;
	const char empty = howManyEmpty(input, pos_x, pos_y);
	const char full = k_max_seats - empty;

	return full;
}
// . = space
// L = empty
// # = full


char applyRules(int pos_x, int pos_y, char* input)
{
	const char spot = input[coord(pos_x, pos_y)];
	if (spot == '.') { return '.'; }
	if (spot == 'L')
	{	// spot is empty
		if (ruleOne(input, pos_x, pos_y))
		{	// 
			return '#'; // return full
		}
		else
		{
			return 'L'; // stay empty
		}
	}
	if (spot == '#')
	{	// spot is full
		if (howManyFull(input, pos_x, pos_y) >= 4)
		{
			return 'L';
		}
		else
		{
			return '#';
		}
	}
	return 0;
}


// If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
// If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
// Otherwise, the seat's state does not change.
