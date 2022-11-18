#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <bitset>
#include <chrono>

using namespace std;

#include "Header.h""

constexpr bool debug = false;

void openFile(std::ifstream & f_inFile, bool debug)
{
	if (debug)
	{
		f_inFile.open("../test.txt");
	}
	else
	{
		f_inFile.open("../input.txt");
	}
	return;
}

template <typename T> inline T isLarger(const T x, const T y)
{	// is X larger than Y?
	return (x > y);
}

template <typename T> inline vector<T> readLine(std::ifstream& f_inFile)
{
	vector<T> input;
	T in = 0;

	while (f_inFile >> in)
	{
		input.push_back(in);
	}
	return input;
}


template <typename T> inline T part1(vector<T> input)
{
	T out = 0;

	for (auto i = 1; i < input.size(); i++)
	{
		const auto y = input[i - 1];
		const auto x = input[i];

		out += isLarger(x, y);
	}

	return out;
}

template <typename T> inline T part2(vector<T> input)
{
	T out = 0;

	for (auto i = 3; i < input.size(); i++)
	{

		const auto a = input[(i - 1) - 2];
		const auto b = input[(i - 1) - 1];
		const auto c = input[(i - 1)];

		const auto A = a + b + c;

		const auto x = input[i - 2];
		const auto y = input[i - 1];
		const auto z = input[i];

		const auto B = x + y + z;

		out += isLarger(B, A);
	}

	return out;
}

int main()
{
	// ----------------------------------------
	// Read input text file
	std::ifstream f_inFile;
	openFile(f_inFile, debug);
	
	vector<int> input;
	int in;
	while (f_inFile >> in)
	{
		input.push_back(in);
	}

	// ----------------------------------------
	const auto result_part1 = part1(input); // 1451
	cout << "Part 1: " << result_part1 << endl;


	const auto result_part2 = part2(input); // 1395
	cout << "Part 2: " << result_part2 << endl;


}