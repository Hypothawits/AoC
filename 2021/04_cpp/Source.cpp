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


template <typename T> inline T part1(vector<vector<vector<T>>> input)
{	// Do part 1!
	auto out = 0;

	


	return out;
}

template <typename T> inline T part2(vector<vector<vector<T>>> input)
{	// Do part 2!
	auto out = 0;

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
	

	vector<string> input;
	string in;

	// get first line as Bingo input
	string bingoRound_text;
	f_inFile >> bingoRound_text;
	
	while (f_inFile >> in)
	{
		input.push_back(in);
	}

	// Convert input text into Bingo! Cards
	auto i = 0;
	while (i < input.size())
	{
		vector <vector<int>> new_bingo_card;

		for (auto y = 0; y < bingo_grid_size_y; y++)
		{
			vector<int> new_bingo_card_line;

			for (auto x = 0; x < bingo_grid_size_x; x++)
			{ // up to 5
				new_bingo_card_line.push_back(stoi(input[i]));
				i++;
			}

			new_bingo_card.push_back(new_bingo_card_line);
		}
		
		bingo_cards.push_back(new_bingo_card);
	}





	if (debug)
	{
		
	}
	else
	{
		
	}
	

	

	// convert to bit array
	for (auto i = 0; i < input.size(); i++)
	{
	
	}
	


	


	// ----------------------------------------
	//const auto result_part1 = part1(input_bits); // 1451
	//cout << "Part 1: " << result_part1 << endl;


	//const auto result_part2 = part2(direction, value); // 1395
	//cout << "Part 2: " << result_part2 << endl;


}