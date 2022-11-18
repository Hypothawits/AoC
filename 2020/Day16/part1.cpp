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

#define k_size 262
struct fieldRange
{
	int r1_min = -1;
	int r1_max = -1;
	int r2_min = -1;
	int r2_max = -1;
	bool colValid[20] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
};

void belongsInOneField(std::vector<fieldRange> fieldVector, int a1, int col)
{




	bool fieldValid[20] = { false };
	int numFieldValid = 0;
	char fieldCount = 0;
	for (auto field : fieldVector)
	{
		const int min = field.r1_min;
		const int max = field.r1_max;
		if ((min <= a1) && (a1 <= max))
		{	// valid for this field
			numFieldValid++;
			fieldValid[fieldCount] = true;
		}


		const int min_ = field.r2_min;
		const int max_ = field.r2_max;
		if ((min_ <= a1) && (a1 <= max_))
		{
			numFieldValid++;
			fieldValid[fieldCount] = true;
		}
		fieldCount++;
		if (numFieldValid > 1) { break; }
	}
	if (numFieldValid == 1)
	{
		for (int i = 0; i < 20; i++)
		{
			if (fieldValid[i] == 1) { std::cout << "column a" << col << " is field: " << i << "\n"; }
		}
	}
}

int main()
{
	auto t1 = std::chrono::high_resolution_clock::now();

	std::vector<string>input;
	input.resize(k_size);

	std::vector<fieldRange>fieldVector;
	fieldVector.resize(20);
	//auto t1 = std::chrono::high_resolution_clock::now();


	std::ifstream f_inFile;
	f_inFile.open("input.txt", ios::in);

	for (int i = 0; i < k_size; i++)
	{
		//std::string in;
		getline(f_inFile, input[i]);

	}

	// Read the value ranges
	int max_range = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int pos = 0; pos < input[i].size(); pos++)
		{
			if (input[i][pos] == ':')
			{

#pragma warning(suppress : 4996)
				sscanf(&input[i][pos], ": %d-%d or %d-%d", &fieldVector[i].r1_min, &fieldVector[i].r1_max, &fieldVector[i].r2_min, &fieldVector[i].r2_max);

				max_range = (max_range < fieldVector[i].r2_max) ? fieldVector[i].r2_max : max_range;

				std::cout << fieldVector[i].r1_min << ":" << fieldVector[i].r1_max << " - " << fieldVector[i].r2_min << ":" << fieldVector[i].r2_max << "\n";
				break;
			}
		}


	}

	// create array of valid!
	std::vector<int>invalid;
	constexpr int buffer = 100;
	invalid.resize(max_range + buffer, 1);

	for (auto field : fieldVector)
	{
		const int min = field.r1_min;
		const int max = field.r1_max;
		for (int x = min; x < max; x++)
		{
			invalid[x] = 0;
		}

		const int min_ = field.r2_min;
		const int max_ = field.r2_max;
		for (int x = min_; x < max_; x++)
		{
			invalid[x] = 0;
		}
	}


	// read in the values and check if valid, sum the values that are not
	long sum = 0;
	int col_row[20][k_size] = { 0 };
	bool validDataLine[k_size] = { 0 };

	for (int i = 25; i < k_size; i++)
	{

#pragma warning(suppress : 4996)
		sscanf(&input[i][0], "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", \
			& col_row[0][i], &col_row[1][i], &col_row[2][i], &col_row[3][i], &col_row[4][i], \
			& col_row[5][i], &col_row[6][i], &col_row[7][i], &col_row[8][i], &col_row[9][i], \
			& col_row[10][i], &col_row[11][i], &col_row[12][i], &col_row[13][i], &col_row[14][i], \
			& col_row[15][i], &col_row[16][i], &col_row[17][i], &col_row[18][i], &col_row[19][i]);

		// part 1
		int allValid = 1;
		for (int j = 0; j < 20; j++)
		{
			sum += col_row[j][i] * invalid[col_row[j][i]];
			const int isValid = invalid[col_row[j][i]];
			allValid = allValid * !(isValid);

		}
		validDataLine[i] = allValid;


	}
	std::cout << "sum of errors: " << sum << "\n";


	//part 2
	char fieldRangeNum = 0;
	for (auto& field : fieldVector)
	{

		const int min = field.r1_min;
		const int max = field.r1_max;

		const int min_ = field.r2_min;
		const int max_ = field.r2_max;
		for (int col = 0; col < 20; col++)
		{

			for (int element = 25; element < k_size; element++)
			{
				if (validDataLine[element])
				{
					int x = col_row[col][element];

					if (!(((min <= x) && (x <= max)) || ((min_ <= x) && (x <= max_))))
					{
						field.colValid[col] = false;
					}
				}
			}


		}
		fieldRangeNum++;
	}

	for (auto field : fieldVector)
	{
		for (int y = 0; y < 20; y++)
		{
			std::cout << field.colValid[y] << " ";
		}
		std::cout << "\n";
	}

	// row class seat

	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();


	std::cout << "\n\n\n";
	std::cout << "result: " << sum << "\n";
	std::cout << "Finished in: " << duration << " microseconds\n\n";
	return 0;

}
