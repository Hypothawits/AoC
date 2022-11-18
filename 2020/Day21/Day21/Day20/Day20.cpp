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

//#define k_inputLines 107 // test
#define k_inputLines 1727 // input


struct tile
{
	int id = 0;

	char top[10];
	char right[10];
	char bottom[10];
	char left[10];

	int NumDotsTop		= 0;
	int NumDotsRight	= 0;
	int NumDotsBottom	= 0;
	int NumDotsLeft		= 0;
	

	char rotation = 0; // 0 = none, 1 = rotate CW 1, 2 = rotate CW 2, etc
	char flip	  = 0; // 'H' = horizontal flip, 'V' = vertical flip 

	bool edge   = 0;
	bool corner = 0;
};

// function to flip line
void flipTileChars(char* input)
{
	char temp[10];
	for (auto i = 0; i < 10; i++)
	{
		temp[i] = input[i];
	}

	int rev = 9;
	for (auto i = 0; i < 10; i++)
	{
		input[i] = temp[rev];
		rev--;
	}
}

bool compareChars(char* x, char* y)
{
	for (auto i = 0; i < 10; i++)
	{
		if (y[i] != x[i]) { return false; }
	}
	return true;
}

void copyChar(char* in, char* out)
{
	for (auto i = 0; i < 10; i++)
	{
		out[i] = in[i];
	}
}

bool findIfMatch(char* in, vector<tile> inputTiles, int currentID)
{
	auto test = in;
	char testFlip[10];
	copyChar(in, testFlip); // copy to test flip
	flipTileChars(testFlip); // flip the array

	// test fliped and non flipped versions on each 
	bool matchFound_bottom = false;
	for (auto tileCompare : inputTiles)
	{
		if (tileCompare.id != currentID)
		{
			const bool a = compareChars(test, tileCompare.top);
			const bool b = compareChars(test, tileCompare.right);
			const bool c = compareChars(test, tileCompare.bottom);
			const bool d = compareChars(test, tileCompare.left);

			const bool e = compareChars(testFlip, tileCompare.top);
			const bool f = compareChars(testFlip, tileCompare.right);
			const bool g = compareChars(testFlip, tileCompare.bottom);
			const bool h = compareChars(testFlip, tileCompare.left);

			// if any match found, return true
			matchFound_bottom = a || b || c || d || e || f || g || h;
			if (matchFound_bottom) { return matchFound_bottom; }
		}
	}
}

// find edges that dont connect with any other edges
	// link these tiles together
		// find corners



int ctoi(char x) { return uint64_t(x - 48); }
char itoc(int x) { return char(x + 48); }
//int = char - 48


int main()
{
	//Start testing
	char test[10]		= { 1,  2, 3, 4, 5, 6, 7, 8, 9, 10 };
	char testFalse[10]	= { 11, 2, 3, 4, 5, 6, 7, 8, 9, 11 };
	char testTrue[10]	= { 1,  2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto isTrue = compareChars(test, testTrue);
	auto isFalse = compareChars(test, testFalse);
	flipTileChars(test);
	//end testing

	auto t1 = std::chrono::high_resolution_clock::now();

	std::vector<string>inputLines;
	inputLines.resize(k_inputLines);

	//auto t1 = std::chrono::high_resolution_clock::now();


	std::ifstream f_inFile;
	//f_inFile.open("test.txt", ios::in);
	f_inFile.open("input.txt", ios::in);

	for (int i = 0; i < k_inputLines; i++)
	{
		//std::string in;
		getline(f_inFile, inputLines[i]);

	}

	// Read the value ranges
	std::vector<tile>inputTiles;
	int tileLineNum = 0;
	auto leftRightcount = 0;
	for (auto &line : inputLines)
	{
		if (line[0] == 'T')
		{	// create new tile and get tile id out
			tile newTile;
			#pragma warning(suppress : 4996)
			const int x = sscanf(&line[0], "Tile %d:", &newTile.id);
			inputTiles.push_back(newTile);

			tileLineNum = 0;
			leftRightcount = 0;
		}
		else if (line[0] == '\0')	{ }
		else
		{
			// add tile data to the lsat created tile
			if (tileLineNum == 0 )
			{	// top
				// take whole line into memory
				int i = 0;
				for (auto c : line)
				{
					inputTiles.back().top[i] = c;
					i++;
				}

				// add corner into left and right
				inputTiles.back().left[leftRightcount] = line[0];
				inputTiles.back().right[leftRightcount] = line[9];
				leftRightcount++;
			}
			else if (tileLineNum == 9)
			{	// bottom
				// take whole line into memory
				int i = 0;
				for (auto c : line)
				{
					inputTiles.back().bottom[i] = c;
					i++;
				}

				// add corner into left and right
				inputTiles.back().left[leftRightcount] = line[0];
				inputTiles.back().right[leftRightcount] = line[9];
				leftRightcount++;
			}
			else
			{	// sides of other lines
				inputTiles.back().left[leftRightcount] = line[0];
				inputTiles.back().right[leftRightcount] = line[9];
				leftRightcount++;
			}
			tileLineNum++;
		}
	}

	// count the number of '.' in each line
	for (auto &tile : inputTiles)
	{
		int dotCount_T = 0;
		int dotCount_R = 0;
		int dotCount_B = 0;
		int dotCount_L = 0;

		for (auto i = 0; i < 10; i++)
		{
			dotCount_T += (tile.top[i] == '.') ? 1 : 0;
			dotCount_R += (tile.right[i] == '.') ? 1 : 0;
			dotCount_B += (tile.bottom[i] == '.') ? 1 : 0;
			dotCount_L += (tile.left[i] == '.') ? 1 : 0;
		}
		
		tile.NumDotsTop		= dotCount_T;
		tile.NumDotsBottom	= dotCount_B;
		tile.NumDotsLeft	= dotCount_L;
		tile.NumDotsRight	= dotCount_R;
	}

	auto debug_edgeCount = 0;
	for (auto &tile : inputTiles)
	{
		auto testTop	= tile.top;
		auto testRight	= tile.right;
		auto testBottom = tile.bottom;
		auto testLeft	= tile.left;

		// test fliped and non flipped versions on each 
		const bool matchFound_T = findIfMatch(testTop,    inputTiles, tile.id);
		const bool matchFound_R = findIfMatch(testRight,  inputTiles, tile.id);
		const bool matchFound_B = findIfMatch(testBottom, inputTiles, tile.id);
		const bool matchFound_L = findIfMatch(testLeft,   inputTiles, tile.id);

		auto edgeFound = !(matchFound_T && matchFound_R && matchFound_B && matchFound_L);
		auto numEdgeFound = 4 - (matchFound_T + matchFound_R + matchFound_B + matchFound_L);
		// if not match found, set this tile to edge!
		if (edgeFound)
		{
			tile.edge = true;
			if (numEdgeFound > 1)
			{
				tile.corner = true;
			}
			debug_edgeCount++;
		}
	}

	// part 1 result
	uint64_t result = 1;
	for (auto& tile : inputTiles)
	{
		if (tile.corner)
		{
			result *= tile.id;
		}
	}
	



	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	cout << "result: " << result << "\n";
	cout << "\n\n\n";
	cout << "Finished in: " << duration << " microseconds\n\n";
	return 0;

}
