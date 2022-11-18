// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <bitset>
// #define k_width 10//92
// #define k_size 10//91
// #define k_size 7
#define k_size 571
using namespace std;

struct mem
{
	unsigned id = 0;
	int64_t data = 0;
};

bool isIDinArray(int id, std::vector<mem> array)
{
	for(auto memAddress : array)
	{
		if(memAddress.id == id)	{ return true;}
	}
	return false;
}

void addMemToVector(std::vector<mem> &array, int memID, int64_t memData)
{
	int index = 0;
	for(auto memAddress : array)
	{
		if(memAddress.id == memID)
		{ 	// address is already in array
			// ipdate data at address
			// std::cout << "index: " << index << "\n";
			// std::cout << "first Val: " << array[index].data << "\n";
			array[index].data = memData;
			// std::cout << "updated Val: " << array[index].data << "\n";
			// memAddress.data = memData;
			return;
		}
		index++;
	}

	// mem ID not in vecotr, add to the vector
	mem newMem;
	newMem.id = memID;
	newMem.data = memData;
	array.push_back(newMem);
	return;
}


int main()
{
	// const int k_size = 91;
	// const int k_width = 92; // 10
	// std::FILE* f_inFile = std::fopen("test.txt", "r");

	std::vector<mem> memVector; // [y][x]
	

	std::ifstream f_inFile;
	f_inFile.open("input.txt", ios::in);
	// f_inFile.open("test.txt", ios::in);

	int64_t x = 0;

	// move mask to outside this if
	int64_t maskVal    = 0; // the mask X are 0
	int64_t maskSelect = 0; // valid data in maskVal
	int64_t dataSelect = 0; // valid data in mem, == ~maskSelect


	for (int i = 0; i < k_size; i++)
	{
		std::string in;
		getline(f_inFile, in);
		
		// Check if memory address "mem" or mask "mask"
		// 36 bit mask
		if(in[1] == 'e')
		{	// is mem
			int64_t memData = 0;
			int memID = 0;
			sscanf(&in[0], "mem[%u] = %lu", &memID, &memData);
			// std::cout << "memID: " << memID << " memData: " << std::bitset<36>(memData) << "\n";

			// apply masks 
			auto getMaskBits = maskVal & maskSelect;
			auto getDataBits = memData & dataSelect;
			auto result = getDataBits | getMaskBits;

			std::cout << "getMaskBits:      " << std::bitset<36>(getMaskBits) << "\n";
			std::cout << "dataSelect:       " << std::bitset<36>(dataSelect) << "\n";
			std::cout << "maskSelect:       " << std::bitset<36>(maskSelect) << "\n";
			// std::cout << "results:          " << std::bitset<36>(result) << " " << result <<"\n\n\n";

			addMemToVector(memVector, memID, result);
			// std::cout << "memVector Result: " << memVector[memVector.size()-1].id << ": " << std::bitset<36>(memVector[0].data) << "\n"; 
			std::cout <<"\n\n";
		}
		else if(in[1] == 'a')
		{	// mask

			// create a new mask
			maskVal    = 0;
			maskSelect = 0;
			dataSelect = 0;
			for(int j = 7; j < 36+7; j++)
			{	// loop through each value in mask

				// std::cout << "in: [" << in[j] << "]\n";
				// std::cout << in[j];

				if(in[j] == '1')
				{
					maskVal += (int64_t(1) << 35 + 7 - j);
					maskSelect += (int64_t(1) << 35 + 7 - j);
				}
				else if(in[j] == '0')
				{
					maskSelect += (int64_t(1) << 35 + 7 - j);
				}
				else
				{ 
					// is 'X'
				}

			}
			dataSelect = ~maskSelect;
			// std::cout << "\nmaskSelect: " << std::bitset<36>(maskSelect) << "\n";
			// std::cout <<   "dataSelect: " << std::bitset<36>(dataSelect) << "\n";

			// apply masks to data
		}

	}

	// std::cout << "test! \n";
	// addMemToVector(memVector, 200, 120);
	// std::cout << "first Val: " << memVector[memVector.size()-1].data << "\n";
	// addMemToVector(memVector, 200, 27);
	// std::cout << "updated Val: " << memVector[memVector.size()-1].data << "\n";
	// addMemToVector(memVector, 156, 243);
	// std::cout << "new Val: " << memVector[memVector.size()-1].data << "\n";

	std::cout << "Read Complete\n";
	std::cout << "mem addresses: " << memVector.size() << "\n";
	// std::exit(0);

	// sum values in memory
	uint64_t sum = 0;
	for(auto memAddress : memVector)
	{
		sum = sum + uint64_t(memAddress.data);
	}

	std::cout << "result: " << sum << "\n";
	
	std::cout << "\n\n\n";
	return 0;
	// 500961422981 is too low
	// 494120436271 is too low (duh)
	// 210286675693 is LOWER
	// 11179633149677
}




