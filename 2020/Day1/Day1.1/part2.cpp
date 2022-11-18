// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int findSummingPair(int *input , const int k_size, const int k_sumResult)
{
    for (int i = 0; i < k_size; i++)
	{
		int val = input[i];
		int search = k_sumResult - val; // 2020 - X must be in the list

		for (int j = 0; j < k_size; j++)
		{
			if (search == input[j])
			{
				std::cout << val << "+" << input[j] << "=" << val + input[j] << "\n";
				return 1;
			}
		}
	}
    return 0;
}

int main()
{
	const int k_size = 200; //array size
	const int k_sumResult = 2020;
	int input[k_size];
	int count = 0;

    std::ifstream f_inFile;
	f_inFile.open("input.txt", ios::in);

	for (int i = 0; i < k_size; i++)
	{
		f_inFile >> input[i];

	}
	
	//std::getline(my_file, x);
	std::cout << "Read Complete\n";




	std::cout << "\n\n NEW \n";
	for (int i = 0; i < k_size; i++)
	{
		int val = input[i];
		int search = k_sumResult - val; // 2020 - X must be in the list

		int result = findSummingPair(input, k_size, search); // search = a + b; a + b + val = 2020
		if (result)
		{
			std::cout << "+" << val << "=" << val + search << "\n";
		}
	}

	std::cout << "\n\n Old \n";
	findSummingPair(input, k_size, k_sumResult);

	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
