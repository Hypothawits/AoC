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

#define k_inputLines 107 // test
//#define k_inputLines 1727 // input


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
	

	char rotation = 0; // 0 = none, 1 = rotate CW once, 2 = rotate CW twice, etc
	char flip	  = 0; // 'H' = horizontal flip, 'V' = vertical flip 

	bool edge   = 0;
	bool corner = 0;

	int  matchesWithID[4] = {0}; 	// {top, right, bottom, left}
	bool matchesFlip[4]; 	// {top, right, bottom, left}
};

void rotateTile(tile &inTile)
{
	char temp;
	for (auto r = 0; r < inTile.rotation; r++)
	{
		for (auto i = 0; i < 10; i++)
		{
			temp = inTile.left[i];
			inTile.left[i] = inTile.bottom[i];
			inTile.bottom[i] = inTile.right[i];
			inTile.right[i] = inTile.top[i];
			inTile.top[i] = temp;
		}

		int temp = inTile.matchesWithID[3];
		inTile.matchesWithID[3] = inTile.matchesWithID[2];
		inTile.matchesWithID[2] = inTile.matchesWithID[1];
		inTile.matchesWithID[1] = inTile.matchesWithID[0];
		inTile.matchesWithID[0] = temp;

		bool b_temp = inTile.matchesFlip[3];
		inTile.matchesFlip[3] = inTile.matchesFlip[2];
		inTile.matchesFlip[2] = inTile.matchesFlip[1];
		inTile.matchesFlip[1] = inTile.matchesFlip[0];
		inTile.matchesFlip[0] = b_temp;

	}

}

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

bool findIfMatch(char* in, vector<tile> &inputTiles, int currentID, char testEdge, tile &inTile)
{
	auto test = in;
	char testFlip[10];
	copyChar(in, testFlip); // copy to test flip
	flipTileChars(testFlip); // flip the array

	// test fliped and non flipped versions on each 
	bool matchFound = false;
	for (auto &tileCompare : inputTiles)
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
			if (a) { // top no flip
				tileCompare.matchesWithID[0] = currentID;
				tileCompare.matchesFlip[0] = 0;
				//switch (testEdge)
				//{
				//case 'T':
				//	tileCompare.rotation = 2;
				//	break;
				//case 'R':
				//	tileCompare.rotation = 1;
				//	break;
				//case 'B':
				//	tileCompare.rotation = 0;
				//	break;
				//case 'L':
				//	tileCompare.rotation = 3;
				//	break;
				//default:
				//	break;
				//}
			}
			if (b) { // right no flip
				tileCompare.matchesWithID[1] = currentID;
				tileCompare.matchesFlip[1] = 0;
				//switch (testEdge)
				//{
				//case 'T':
				//	tileCompare.rotation = 3;
				//	break;
				//case 'R':
				//	tileCompare.rotation = 2;
				//	break;
				//case 'B':
				//	tileCompare.rotation = 1;
				//	break;
				//case 'L':
				//	tileCompare.rotation = 0;
				//	break;
				//default:
				//	break;
				//}
			}
			if (c) { // bottom no flip
				tileCompare.matchesWithID[2] = currentID;
				tileCompare.matchesFlip[2] = 0;
				//switch (testEdge)
				//{
				//case 'T':
				//	tileCompare.rotation = 0;
				//	break;
				//case 'R':
				//	tileCompare.rotation = 3;
				//	break;
				//case 'B':
				//	tileCompare.rotation = 2;
				//	break;
				//case 'L':
				//	tileCompare.rotation = 1;
				//	break;
				//default:
				//	break;
				//}
			}
			if (d) { //left no flip
				tileCompare.matchesWithID[3] = currentID;
				tileCompare.matchesFlip[3] = 0;
				//switch (testEdge)
				//{
				//case 'T':
				//	tileCompare.rotation = 1;
				//	break;
				//case 'R':
				//	tileCompare.rotation = 0;
				//	break;
				//case 'B':
				//	tileCompare.rotation = 3;
				//	break;
				//case 'L':
				//	tileCompare.rotation = 2;
				//	break;
				//default:
				//	break;
				//}
			}

			// flip stuff
			if (e) { // top flip
				tileCompare.matchesWithID[0] = currentID;
				tileCompare.matchesFlip[0] = 1;
				//switch (testEdge)
				//{
				//case 'T':
				//	tileCompare.rotation = 2;
				//	break;
				//case 'R':
				//	tileCompare.rotation = 1;
				//	break;
				//case 'B':
				//	tileCompare.rotation = 0;
				//	break;
				//case 'L':
				//	tileCompare.rotation = 3;
				//	break;
				//default:
				//	break;
				//}
			}
			if (f) { // right flip
				tileCompare.matchesWithID[1] = currentID;
				tileCompare.matchesFlip[1] = 1;
				//switch (testEdge)
				//{
				//case 'T':
				//	tileCompare.rotation = 3;
				//	break;
				//case 'R':
				//	tileCompare.rotation = 2;
				//	break;
				//case 'B':
				//	tileCompare.rotation = 1;
				//	break;
				//case 'L':
				//	tileCompare.rotation = 0;
				//	break;
				//default:
				//	break;
				//}
			}
			if (g) { // bottom flip
				tileCompare.matchesWithID[2] = currentID;
				tileCompare.matchesFlip[2] = 1;
				//switch (testEdge)
				//{
				//case 'T':
				//	tileCompare.rotation = 0;
				//	break;
				//case 'R':
				//	tileCompare.rotation = 3;
				//	break;
				//case 'B':
				//	tileCompare.rotation = 2;
				//	break;
				//case 'L':
				//	tileCompare.rotation = 1;
				//	break;
				//default:
				//	break;
				//}
			}
			if (h) { //left flip
				tileCompare.matchesWithID[3] = currentID;
				tileCompare.matchesFlip[3] = 1;
				//switch (testEdge)
				//{
				//case 'T':
				//	tileCompare.rotation = 1;
				//	break;
				//case 'R':
				//	tileCompare.rotation = 0;
				//	break;
				//case 'B':
				//	tileCompare.rotation = 3;
				//	break;
				//case 'L':
				//	tileCompare.rotation = 2;
				//	break;
				//default:
				//	break;
				//}
			}

			matchFound = a || b || c || d || e || f || g || h;
			if (matchFound) { return matchFound; }
		}
	}

	return false;
}


auto getTileByID(int ID, vector<tile>& inputTiles )
{
	for (auto& tile : inputTiles)
	{
		if (tile.id == ID)
		{
			return tile;
		}
	}
}

// find edges that dont connect with any other edges
	// link these tiles together
		// find corners



int  ctoi(char x) { return uint64_t(x - 48); }
char itoc(int x)  { return     char(x + 48); }
//int = char - 48


int main()
{
	//Start testing
	char test[10]		= { 1,  2, 3, 4, 5, 6, 7, 8, 9, 10 };
	char testFalse[10]	= { 11, 2, 3, 4, 5, 6, 7, 8, 9, 11 };
	char testTrue[10]	= { 1,  2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto isTrue  = compareChars(test, testTrue);
	auto isFalse = compareChars(test, testFalse);
	flipTileChars(test);
	//end testing

	auto t1 = std::chrono::high_resolution_clock::now();

	std::vector<string>inputLines;
	inputLines.resize(k_inputLines);

	//auto t1 = std::chrono::high_resolution_clock::now();


	std::ifstream f_inFile;
	f_inFile.open("test.txt", ios::in);
	//f_inFile.open("input.txt", ios::in);

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
		const bool matchFound_T = findIfMatch(testTop,    inputTiles, tile.id, 'T', tile);
		const bool matchFound_R = findIfMatch(testRight,  inputTiles, tile.id, 'R', tile);
		const bool matchFound_B = findIfMatch(testBottom, inputTiles, tile.id, 'B', tile);
		const bool matchFound_L = findIfMatch(testLeft,   inputTiles, tile.id, 'L', tile);

		auto edgeFound    = !(matchFound_T && matchFound_R && matchFound_B && matchFound_L);
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

	// part two, build the image
	tile pictureTiles[25][25];
	
	// Rotate things
	for (auto& tile : inputTiles)
	{
		rotateTile(tile);
	}

	// Find top left corner
	for (auto& tile : inputTiles)
	{
		if (tile.corner)
		{	// is corner
			//check if top left corner

			// top right bottom left
			if ((tile.matchesWithID[0] == 0) && (tile.matchesWithID[3] == 0))
			{	// tile is top left corner
				pictureTiles[0][0] = tile;
			}
		}
	}


	for (auto x = 0; x < 25; x++)
	{
		for (auto y = 0; y < 25; y++)
		{
			if(pictureTiles[y][x].id)
			{ 
				auto nextID_T = pictureTiles[y][x].matchesWithID[0];
				auto nextID_R = pictureTiles[y][x].matchesWithID[1];
				auto nextID_B = pictureTiles[y][x].matchesWithID[2];
				auto nextID_L = pictureTiles[y][x].matchesWithID[3];

				if (nextID_T != 0) { pictureTiles[y - 1][x] = getTileByID(nextID_T, inputTiles); }
				if (nextID_R != 0) { pictureTiles[y][x + 1] = getTileByID(nextID_R, inputTiles); }
				if (nextID_B != 0) { pictureTiles[y + 1][x] = getTileByID(nextID_B, inputTiles); }
				if (nextID_L != 0) { pictureTiles[y][x - 1] = getTileByID(nextID_L, inputTiles); }
			}
		}
	}
	


	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	cout << "result: " << result << "\n";
	cout << "\n\n\n";
	cout << "Finished in: " << duration << " microseconds\n\n";
	return 0;

}
