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

#define k_size 10 //378

struct line
{
	char input[200] = {0};
};

int ctoi(char x){	return uint64_t(x - 48);}
char itoc(int x) { return char(x + 48); }
//int = char - 48

// 2 * 3 + (4 * 5)
// 5 + (8 * 3 + 9 + 3 * 4 * 3)
//	5 + (432)
uint64_t calcLinePart1(char line[200], int &pos, uint64_t LHS)
{
	
	while (line[pos] != '\0')
	{
		char debugValue = line[pos];
		switch (line[pos])
		{
		case '+':
			pos++;
			return LHS += calcLinePart1(line, pos, LHS);
			break;
		case '*':
			pos++;
			return LHS *= calcLinePart1(line, pos, LHS);
			break;
		case '(':
			pos++;
			LHS = calcLinePart1(line, pos, 0); // return sumprod of rest of line, but start from zero again.
			break;
		case ')':
			pos++;
			return LHS;
			break;

		default:
			LHS = uint64_t(line[pos] - 48); // ctoi(line[pos]);
			pos++;
			break;
		}
		//pos++;
	}

	return LHS;
}

uint64_t calcLine(char line[200], int& pos, uint64_t LHS)
{

	while (line[pos] != '\0')
	{
		char debugValue = line[pos];
		switch (line[pos])
		{
		case '+':
			pos++;
			return LHS += calcLine(line, pos, LHS);
			break;
		case '*':
			pos++;
			return LHS *= calcLine(line, pos, LHS);
			break;
		case '(':
			pos++;
			LHS = calcLine(line, pos, 0); // return sumprod of rest of line, but start from zero again.
			break;
		case ')':
			pos++;
			return LHS;
			break;

		default:
			LHS = uint64_t(line[pos]) - 48; // ctoi(line[pos]);
			pos++;
			break;
		}
		
	}

	return LHS;
}

int main()
{
	auto t1 = std::chrono::high_resolution_clock::now();

	std::vector<string>input;
	
	input.resize(k_size);
	std::vector<line>input_lines;
	input_lines.resize(k_size);
	//auto t1 = std::chrono::high_resolution_clock::now();

	
	std::ifstream f_inFile;
	f_inFile.open("test.txt", ios::in);

	for (int i = 0; i < k_size; i++)
	{
		//std::string in;
		getline(f_inFile, input[i]);

	}

	// Read the value ranges
	int inputLine_index = 0;
	for (auto line : input)
	{
		int char_index = 0;
		for (int i = line.size()-1; i >= 0 ; i--)
		{
			if (line[i] != ' ')
			{
				// flip the brackets for my little brain to read better
				if(line[i] == ')')
				{ 
					input_lines[inputLine_index].input[char_index] = '(';
				}
				else if (line[i] == '(')
				{
					input_lines[inputLine_index].input[char_index] = ')';
				}
				else
				{
					input_lines[inputLine_index].input[char_index] = line[i];
				}
				
				char_index++;
			}
		}
		inputLine_index++;

		//#pragma warning(suppress : 4996)
		/*sscanf(&input[i][pos], ": %d-%d or %d-%d", &fieldVector[i].r1_min, &fieldVector[i].r1_max, &fieldVector[i].r2_min, &fieldVector[i].r2_max);
		*/
	}

	int pos = 0;
	uint64_t sum = 0;
	for (int i = 0; i < k_size; i++)
	{
		pos = 0;
		uint64_t result = calcLine(input_lines[i].input, pos, 0);
		cout << result << "\n";
		sum += result;
	}

	// do the sums
	string test = input_lines[1].input;
	for (int i = 0; i < k_size; i++)
	{
		if (test[i] == '+')
		{
			// check if operators are numbers
			if (test[i - 1] != ')' && test[i + 1] != '(')
			{
				const int x = ctoi(test[i - 1]) + ctoi(test[i + 1]);
				test[i - 1] = ' ';
				test[i + 0] = ' ';
				test[i + 1] = itoc(x);
			}
		}
		
		
	}



	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	cout << "result: " << sum << "\n";
	cout << "\n\n\n";
	cout << "Finished in: " << duration << " microseconds\n\n";
	return 0;

}

// 689976794 too low
// 202553439706