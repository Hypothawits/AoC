#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <bitset>
#include <chrono>
#include<sstream>

using namespace std::chrono;
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


template <typename T> inline T part1(T input)
{	// Do part 1!
	auto out = 0;



	return out;
}

template <typename T> inline T part2(T input)
{	// Do part 2!
	T out = 0;



	return out;
}

int main()
{
	constexpr auto bingo_grid_size_x = 5;
	constexpr auto bingo_grid_size_y = 5;

	vector<vector<vector<int>>> bingo_cards;

	// ----------------------------------------
	// Read input text file
	std::ifstream f_inFile;
	openFile(f_inFile, debug);
	
	vector<string> input_raw;

	// get first line as Bingo input
	while (f_inFile)
	{
		string substr;
		getline(f_inFile, substr);
		input_raw.push_back(substr);
	}

	vector<string> input;
	vector<string> code;

	for (auto i = 0; i < input_raw.size()-1; i++)
	{
		// convert line to stream
		stringstream s_stream(input_raw[i]);
		string substr;
		getline(s_stream, substr, '|');
		
		input.push_back(substr);
		code.push_back(input_raw[i].substr(substr.length() +2));
	}

	vector<vector<string>> segments;
	string in;
	for (auto i = 0; i < input_raw.size() - 1; i++)
	{
		vector<string> seg;
		stringstream s_stream(input[i]);
		string segment;
		while (s_stream >> segment)
		{
			seg.push_back(segment);
		}
		segments.push_back(seg);
	}
	
	//--------
	int currentCodeLocations[10] = { -1,-1, -1, -1, -1, -1, -1, -1, -1, -1 };
	// top topR mid botR bot botL topL
	char segmentCode[10] = {};
	for (auto i = 0; i < 10; i++)
	{
		switch (segments[0][i].length())
		{
		case 2:
			currentCodeLocations[i] = 1;
			break;
		case 3:
			currentCodeLocations[i] = 7;
			break;
		case 4:
			currentCodeLocations[i] = 4;
			break;
		case 7:
			currentCodeLocations[i] = 8;
			break;
		default:
			break;
		}
	}

	for (auto i = 0; i < 10; i++)
	{
		switch (segments[0][i].length())
		{
		case 1:
			break;
		default:
			break;
		}

	}

	if (debug)
	{
		//stop here
		int x = 0;
	}
	else
	{
		
	}
	

	


	

	
	// ----------------------------------------
	auto start1 = high_resolution_clock::now();

	
	//const auto result_part1 = part1(fishAge);

	auto stop1 = high_resolution_clock::now();


	
	
	// ----------------------------------------
	auto start2 = high_resolution_clock::now();


	//const auto result_part2 = part2(fishAge);
	
	auto stop2 = high_resolution_clock::now();


	// ----------------------------------------
	//cout << "Part 1: " << result_part1 << endl;
	//cout << "Part 2: " << result_part2 << endl;
	// ----------------------------------------


	auto duration_ns1 = duration_cast<nanoseconds>(stop1 - start1);
	auto duration_ms1 = duration_cast<microseconds>(stop1 - start1);
	auto duration_ns2 = duration_cast<nanoseconds>(stop2 - start2);
	auto duration_ms2 = duration_cast<microseconds>(stop2 - start2);
	
	cout << "Time Part 1: " << duration_ms1.count() << " microseconds" << endl;
	cout << "Time Part 1: " << duration_ns1.count() << " nanoseconds" << endl;

	cout << "Time Part 2: " << duration_ms2.count() << " microseconds" << endl;
	cout << "Time Part 2: " << duration_ns2.count() << " nanoseconds" << endl;
}