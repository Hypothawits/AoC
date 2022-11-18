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

#define k_size 30000000

int main()
{
	auto t1 = std::chrono::high_resolution_clock::now();

	constexpr auto k_inLength = 7;
	uint32_t input[k_inLength] = { 7,14,0,17,11,1,2 };
	//uint64_t input[k_inLength] = { 0, 3, 6 };

	std::vector<uint32_t>lastCalled;
	lastCalled.resize(k_size, 0);
	//auto t1 = std::chrono::high_resolution_clock::now();

	uint32_t lastNumSpoken = input[k_inLength - 1];


	/*lastCalled[0] = 1;
	lastCalled[3] = 2;
	lastCalled[6] = 3;*/

	lastCalled[7] = 1;
	lastCalled[14] = 2;
	lastCalled[0] = 3;
	lastCalled[17] = 4;
	lastCalled[11] = 5;
	lastCalled[1] = 6;
	lastCalled[2] = 7;

	for (uint32_t turn = k_inLength + 1; turn < k_size + 1; turn++)
	{
		const auto lastTurn = turn - 1;
		const auto lastC = lastCalled[lastNumSpoken];
		//const auto x = lastC == 0;
		//const auto y = lastTurn * x;
		//const auto z = (lastC + (y));
		const auto thisTurnResult = (lastTurn)-(lastC + (lastTurn * (lastC == 0)));
		lastCalled[lastNumSpoken] = lastTurn;

		lastNumSpoken = thisTurnResult;
	}


	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();


	std::cout << "\n\n\n";
	std::cout << "result: " << lastNumSpoken << "\n";
	std::cout << "Finished in: " << duration << " microseconds\n\n";
	return 0;

}

// 4272138 us with memory allocation
// 1774270 us without memory allocation
// 594912 us release with mempry allocation (no visual studio)
// 507737 us release without memory allocation
// 436034 uint32 in memory 