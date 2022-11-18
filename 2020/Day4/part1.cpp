#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

#define k_lines 1146
// #define k_size_y 323
using namespace std;

enum portData {byr, iyr, eyr, hgt, hcl, ecl, pid, cip};

char convertField(std::string in);

struct passport
{
    int byr = -1;//Birth Year
    int iyr = -1;//Issue Year
    int eyr = -1;//Expiration Year
    int hgt = -1;//Height
	char hgt_unit; // Height Units
    std::string hcl;//Hair Color
    std::string ecl;//Eye Color
    std::string pid;//Passport ID
    std::string cid;//Country ID
};

int main()
{

	std::ifstream f_inFile;
	f_inFile.open("input.txt", ios::in);

	std::vector<std::string> portVector; 
	passport passportVactor[k_lines];

	std::string newPort;
	portVector.push_back(newPort);
	// f_inFile.open("test.txt", ios::in);

	int portCount = 0;
	for (int i = 0; i < (k_lines); i++)
	{
		std::string in;
		getline(f_inFile, in);
		if(in[0] == '\0')
		{
			portCount++;
			std::string newPort;
			portVector.push_back(newPort);
			// std::cout << "newLine\n"; 
		}
		else
		{
			portVector[portCount].append(" ");
			portVector[portCount].append(in);
			// std::cout << in << "\n";
		}
	}

	std::cout << "Read Complete\n";

	std::cout << "Passport 1\n";
	std::cout << portVector[0] << "\n"; 


	std::cout << "Test eyr: " << int(convertField("eyr")) <<"\n";

	for (int i = 0; i < k_lines; i++)
	{
		std::string currentP = portVector[i];
		for (int c = 0; c < currentP.size(); c++)
		{
			if(currentP[c] == ':')
			{	// found a data entry
				int label_int = currentP[c-3] + currentP[c-2] + currentP[c-1];
				char label = convertField(label);

			}
		}
	}


	return 0;
}


void assignValue(passport* passV, int passIndex, string data )
{

	int data_int, string data_str

	switch (label)
	{
	case byr:
		passV[passIndex].byr = data_int;
		break;
	
	case iyr:
		passV[passIndex].iyr = data_int;
		break;
	
	case eyr:
		passV[passIndex].eyr = data_int;
		break;
	
	case hgt:
		passV[passIndex].hgt = data_int;
		break;
	
	case hcl:
		passV[passIndex].hcl = data_str;
		break;
	
	case ecl:
		passV[passIndex].ecl = data_str;
		break;
	
	case pid:
		passV[passIndex].pid = data_str;
		break;
	
	case cip:
		passV[passIndex].cid = data_str;
		break;
	
	default:
		break;
	}
}





char convertField(int input)
{
	// int input = in[0] + in[1] + in[2];
	switch (input)
	{
	case 'b' + 'y' + 'r':
		return byr;
		break;
	
	case 'i' + 'y' + 'r':
		return iyr;
		break;
	
	case 'e' + 'y' + 'r':
		return eyr;
		break;
	
	case 'h' + 'g' + 't':
		return hgt;
		break;
	
	case 'h' + 'c' + 'l':
		return hcl;
		break;
	
	case 'e' + 'c' + 'l':
		return ecl;
		break;
	
	case 'p' + 'i' + 'd':
		return pid;
		break;
	
	case 'c' + 'i' + 'p':
		return cip;
		break;
	
	default:
		return -1;
		break;
	}
}
