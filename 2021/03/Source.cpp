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

template <typename T> inline T bin2int(vector<T> bits)
{
	auto out = 0;
	for (auto i = 0; i < bits.size(); i++)
	{
		out += bits[bits.size()-1 - i] * pow(2, i);
	}
	return out;
}


template <typename T> inline T part1(vector<vector<T>> input)
{	// Do part 1!
	auto out = 0;

	vector<T> bits_out;
	vector<T> bits_out_comp;

	for (auto bitPos = 0; bitPos < input[0].size(); bitPos++)
	{
		auto medi_val = 0;

		for (auto i = 0; i < input.size(); i++)
		{

			medi_val += input[i][bitPos];

		}

		bits_out.push_back( medi_val / (input.size()/2 ) );
	}

	auto out1 = bin2int(bits_out);

	for (auto bitPos = 0; bitPos < input[0].size(); bitPos++)
	{
		if (bits_out[bitPos])
		{
			bits_out_comp.push_back(0);
		}
		else {
			bits_out_comp.push_back(1);
		}
		
	}

	auto out2 = bin2int(bits_out_comp);


	return out1 * out2;
}

template <typename T> inline T part2(vector<vector<T>> input)
{	// Do part 2!
	vector<T> bits_out;
	vector<T> bits_out_comp;

	int numOfBits = input.size();

	for (auto i = 0; i < value.size(); i++)
	{

	}

	auto out = 0;

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

	auto numBits = 0;
	if (debug)
	{
		numBits = 5;
	}
	else
	{
		numBits = 12;
	}
	
	vector<vector<int>> input_bits;

	// convert to bit array
	for (auto i = 0; i < input.size(); i++)
	{
		vector<int> temp_bits;

		for (auto j = 0; j < numBits; j++)
		{
			
			temp_bits.push_back(input[i][j] - 48); // offset char to int
		}

		input_bits.push_back(temp_bits);
	}
	


	


	// ----------------------------------------
	const auto result_part1 = part1(input_bits); // 1451
	cout << "Part 1: " << result_part1 << endl;


	//const auto result_part2 = part2(direction, value); // 1395
	//cout << "Part 2: " << result_part2 << endl;


}