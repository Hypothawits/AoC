#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
// #define k_width 10//92
// #define k_size 10//91
#define k_width 10
#define k_size 761
using namespace std;

int convert(string in);
bool isInArray(vector<int> in, int x);

int main()
{
	string input[k_size]; // [y][x]

	std::ifstream f_inFile;
	f_inFile.open("input.txt", ios::in);
	// f_inFile.open("test.txt", ios::in);

	for (int i = 0; i < k_size; i++)
	{
		getline(f_inFile, input[i]);
	}

	// for(int i = 0; i < k_size; i++)
	// {
	// 	std::cout << input[i] << "\n";
	// }
	std::cout << "Read Complete\n";

	// row range  0 to 127
	// seat range 0 to 7

	// F = 0
	// B = 1
	// R = 1
	// L = 0

	// convert FBRL to binary

	int maxTicket = 0;

	// std::cout << convert(input[0]) << "\n";
	// std::cout << convert(input[1]) << "\n";
	// std::cout << convert(input[2]) << "\n";
	
	vector<int> ticketList;

	for(int i = 0; i < k_size; i++)
	{
		int test = convert(input[i]);
		ticketList.push_back(test);

		if(test > maxTicket)
		{
			maxTicket = test;
		}
	}

	std::cout << "maxTicket" << maxTicket << "\n";

	sort(ticketList.begin(), ticketList.end());

	for (int test = 0; test < k_size; test++)
	{
		bool inArray = isInArray(ticketList, test);
		if(!inArray)
		{	// could find in array, check seat in front and behind is full
			bool nextToo = isInArray(ticketList, test-1);
			bool nextThree = isInArray(ticketList, test+1);
			if(nextToo && nextThree)
			{
				std::cout << "Your Seat: " << test << "\n";
				break;
			}
		}
		
	}




	std::cout << "\n\n\n";
	return 0;
}

bool isInArray(vector<int> in, int x)
{
	for (int index = 0; index < k_size; index++)
	{
		if(x == in[index]){return true;}
	}
	return false;
}

int convert(string in)
{
	int out = 0b0000000000;
	for (int i = 0; i < in.size(); i++)
	{
		switch (in[i])
		{
		case 'B':
		case 'R':
			// out = out | (0b0000000001 << i);
			out = out | (0b1000000000 >> i);
			break;
		
		default:
			break;
		}
	}
	return out;
}

