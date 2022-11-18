// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
using namespace std;

enum inst { jop, acc, nop };

bool isNumber(char in)
{
	switch (in)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return 1;
		break;
	
	default:
		//NAN
		return 0;
		break;
	}
}



inst checkAndSwap(inst* instruction, int pos, int swapIndex){
	if(pos == swapIndex)
	{
		if(instruction[pos] == jop)
		{
			return nop;
		}
		else if(instruction[pos] == nop)
		{
			return jop;
		}
		else
		{
			return 	instruction[pos];
		}
	}
	else
	{
		return 	instruction[pos];
	}
	
}

int main()
{
	const int k_size = 623;
	std::string input[k_size];

	std::FILE* f_inFile = std::fopen("input.txt", "r");
	
	char c_instruction [k_size][3];
	inst instruction[k_size];
	int instrVal [k_size];
	bool repeat [k_size];

	for (int i = 0; i < k_size; i++)
	{
		fscanf(f_inFile, "%s %d", c_instruction[i], &(instrVal[i]));
		repeat[i] = 1;
	}

	for(int i = 0; i < k_size; i++)
	{
		if(c_instruction[i][0] == 'j')
		{
			instruction[i] = jop;
		}
		else if (c_instruction[i][0] == 'a')
		{ 
			instruction[i] = acc;
		}
		else
		{
			instruction[i] = nop;
		}
	}

	std::cout << "Read Complete\n";
	
	for (int swapIndex = 0; swapIndex < k_size; swapIndex++)
	{
		int pos = 0;
		int accum = 0;
		int count = 0;
		
		while(repeat[pos] && (pos != 622))
		{
			count++;
			inst currentInstr = checkAndSwap(instruction, pos, swapIndex);

			switch (currentInstr)
			{
			case jop:
				repeat[pos] = 0;
				pos += instrVal[pos];
				break;
			case acc:
				repeat[pos] = 0;
				accum += instrVal[pos];
				pos++;
				break;
			case nop:
				repeat[pos] = 0;
				pos++;			
				break;
			default:
				std::cout << "Error: Unknown Instruction \n";
				break;
			}
		}

		if(pos == 622)
		{	// reached end of program
			std::cout << "Found it! " << "count: " << count << " accum: " << accum << "\n"; 
		}

		for (int i = 0; i < k_size; i++)
		{
			repeat[i] = 1;
		}
	}
 	std::cout << "\n\n\n";
	return 0;

}

// the rewrite I didnt need
int runProgram(bool* repeat, inst* instruction, int* instrVal, int &count)
{
	int pos = 0;
	int accum = 0;
	while(repeat[pos] && (pos != 622))
	{
		count++;
		inst currentInstr = instruction[pos];

		switch (currentInstr)
		{
		case jop:
			repeat[pos] = 0;
			pos += instrVal[pos];
			break;
		case acc:
			repeat[pos] = 0;
			accum += instrVal[pos];
			pos++;
			break;
		case nop:
			repeat[pos] = 0;
			pos++;			
			break;
		default:
			std::cout << "Error: Unknown Instruction \n";
			break;
		}
	}
	return accum;
}
		