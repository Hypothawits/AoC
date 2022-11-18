// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

#define k_size_x 31
#define k_size_y 323
using namespace std;

struct vec
{
	int x = 0;
	int y = 0;
};

bool isTree(char in);
int countTheTrees(int xMove, int yMove, char map[k_size_y][k_size_x]);

int main()
{
	char map[k_size_y][k_size_x];//[y][x] 323 x 31

	std::ifstream f_inFile;
	f_inFile.open("input.txt", ios::in);
	// f_inFile.open("test.txt", ios::in);

	for (int i = 0; i < (k_size_y); i++)
	{
		std::string in;
		getline(f_inFile, in);
		for (int j = 0; j < k_size_x; j++)
		{
			map[i][j] = in[j];
		}

	}

	std::cout << "Read Complete\n";

	for (int j = 0; j < k_size_x; j++)
	{
		std::cout << map[0][j];
	}
	std::cout << "\n";
	
	for (int j = 0; j < k_size_x; j++)
	{
		std::cout << map[1][j];
	}
	std::cout << "\n";

	std::cout << "Do the thing\n";

	// vec move;
	// move.x = 3;
	// move.y = 1;

	// vec pos;
	// pos.x = 0;
	// pos.y = 0;

	long unsigned treeCount0 = countTheTrees(1,1, map);
	long unsigned treeCount1 = countTheTrees(3,1, map);
	long unsigned treeCount2 = countTheTrees(5,1, map);
	long unsigned treeCount3 = countTheTrees(7,1, map);
	long unsigned treeCount4 = countTheTrees(1,2, map);
	
	std::cout << "Result: " << treeCount0*treeCount1*treeCount2*treeCount3*treeCount4 << "\n";

	return 0;
}

int countTheTrees(int xMove, int yMove, char map[k_size_y][k_size_x])
{
	vec move;
	move.x = xMove;
	move.y = yMove;

	vec pos;
	pos.x = 0;
	pos.y = 0;

	int treeCount = 0;
	while (pos.y < k_size_y)
	{	// go until pos y is lower than height of hill
		
		pos.y += move.y; // increase y
		pos.x += move.x;
		// check if going over the edge
		if(pos.x >= k_size_x)
		{
			pos.x -= k_size_x; 
		}
		treeCount += isTree(map[pos.y][pos.x]);
	}
	std::cout << "tree count: " << treeCount << "\n";
	return treeCount;
}



bool isTree(char in)
{
	return (in == '#') ? true : false;
}

