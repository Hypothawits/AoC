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


template <typename T> inline T part1(T* fishAge, T* fishNumbers, const int maxNumDays)
{	// Do part 1!
	auto out = 0;

	// Shift values left (reduce age by 1)
	for (auto day = 0; day < maxNumDays+1; day++)
	{
		// Get the number that birth
		const auto numBirth = fishNumbers[0];
		// Shift all other numbers Left
		fishNumbers[0] = fishNumbers[1];
		fishNumbers[1] = fishNumbers[2];
		fishNumbers[2] = fishNumbers[3];
		fishNumbers[3] = fishNumbers[4];
		fishNumbers[4] = fishNumbers[5];
		fishNumbers[5] = fishNumbers[6];
		fishNumbers[6] = fishNumbers[7];
		fishNumbers[7] = fishNumbers[8];
		fishNumbers[8] = 0; // shift in zeros

		// Add new fish to start at 8
		fishNumbers[8] = numBirth;

		// Add reset fish to start at 6
		fishNumbers[6] += numBirth;

	}

	// Sum the number of Fish after maxNumDays
	for (auto i = 0; i < 8; i++)
	{
		out += fishNumbers[i];
	}



	return out;
}

template <typename T> inline T part2(T* fishAge, T* fishNumbers, const int maxNumDays)
{	// Do part 2!
	T out = 0;

	// Shift values left (reduce age by 1)
	for (auto day = 0; day < maxNumDays + 1; day++)
	{
		// Get the number that birth
		const T numBirth = fishNumbers[0];
		// Shift all other numbers Left
		fishNumbers[0] = fishNumbers[1];
		fishNumbers[1] = fishNumbers[2];
		fishNumbers[2] = fishNumbers[3];
		fishNumbers[3] = fishNumbers[4];
		fishNumbers[4] = fishNumbers[5];
		fishNumbers[5] = fishNumbers[6];
		fishNumbers[6] = fishNumbers[7];
		fishNumbers[7] = fishNumbers[8];
		fishNumbers[8] = 0; // shift in zeros

		// Add new fish to start at 8
		fishNumbers[8] = numBirth;

		// Add reset fish to start at 6
		fishNumbers[6] += numBirth;

	}

	// Sum the number of Fish after maxNumDays
	for (auto i = 0; i < 8; i++)
	{
		out += fishNumbers[i];
	}



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
	

	vector<char> input;
	string in;
	f_inFile >> in;
	stringstream s_stream(in);
	
	while (s_stream.good()) {
		string substr;
		getline(s_stream, substr, ',');

		input.push_back(stoi(substr));
	}
	

	unsigned long long fishAge[9] = { 0,1,2,3,4,5,6,7,8 };
	unsigned long long numberOfFishByAge[9] = { 0,0,0,0,0,0,0,0 };

	for (auto i = 0; i < input.size(); i++)
	{
		numberOfFishByAge[input[i]] += 1;
	}




	if (debug)
	{
		//stop here
		int x = 0;
	}
	else
	{
		
	}
	

	

	for (auto i = 0; i < input.size(); i++)
	{
	
	}
	


	

	
	// ----------------------------------------
	auto start1 = high_resolution_clock::now();

	const int maxNumDays = 80;
	const auto result_part1 = part1(fishAge, numberOfFishByAge, maxNumDays); //Debug 5934

	auto stop1 = high_resolution_clock::now();


	
	
	// ----------------------------------------
	auto start2 = high_resolution_clock::now();

	const int maxNumDays_p2 = 256;
	const auto result_part2 = part2(fishAge, numberOfFishByAge, maxNumDays_p2); // 1395
	
	auto stop2 = high_resolution_clock::now();


	// ----------------------------------------
	cout << "Part 1: " << result_part1 << endl;
	cout << "Part 2: " << result_part2 << endl;
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