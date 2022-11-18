#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <bitset>
#include <chrono>

using namespace std;

#include "Header.h"

template <typename T> inline T part1(vector<string> direction, vector<T>  value)
{	// Do part 1!
	T depth = 0;
	T forward = 0;
	for (auto i = 0; i < value.size(); i++)
	{
		if (direction[i] == "forward")
		{
			forward += value[i];
		}
		else if (direction[i] == "down")
		{
			depth += value[i];
		}
		else // up
		{
			depth -= value[i];
		}
	}

	auto out = depth * forward;

	return out;
}

template <typename T> inline T part2(vector<string> direction, vector<T>  value)
{	// Do part 1!
	T depth		= 0;
	T forward	= 0;
	T aim		= 0;
	for (auto i = 0; i < value.size(); i++)
	{
		if (direction[i] == "forward")
		{
			forward += value[i];
			depth += value[i] * aim;
		}
		else if (direction[i] == "down")
		{
			aim += value[i];
		}
		else // up
		{
			aim -= value[i];
		}
	}

	auto out = depth * forward;

	return out;
}

int main()
{
	// ----------------------------------------
	// Read input text file
	std::ifstream f_inFile;
	openFile(f_inFile, debug);
	

	vector<string> input;
	string in;
	while (f_inFile >> in)
	{
		input.push_back(in);
	}

	// split Direction value pair

	vector<string> direction;
	vector<int>    value;

	for (auto i = 1; i < input.size(); i = i + 2)
	{
		direction.push_back(input[i-1]);
		value.push_back(stoi(input[i]));
	}

	if (debug)
	{
		cout << input[0] << endl;
		cout << input[1] << endl;
		cout << endl;
		cout << direction[0] << endl;
		cout << value[0] << endl;
	}
	


	// ----------------------------------------
	const auto result_part1 = part1(direction, value); // 1451
	cout << "Part 1: " << result_part1 << endl;


	const auto result_part2 = part2(direction, value); // 1395
	cout << "Part 2: " << result_part2 << endl;


}