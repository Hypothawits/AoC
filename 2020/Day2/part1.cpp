// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int countCharInString(const std::string keyChar, const int minChar, const int maxChar, const std::string key)
{
	int charCount = 0;
	
	const char c_keyChar = keyChar[0];

	for (int i=0; i < key.length(); i++)
	{
		const char c_key = key[i];
		//std::cout << c_key << " - " << c_keyChar << "\n";

		if (c_key == c_keyChar)
		{
			charCount++;
			//std::cout << charCount << "\n";
		}
	}

	//std::cout << "minChar: " << minChar << "\n";
	//std::cout << "maxChar: " << maxChar << "\n";
	//std::cout << "charCount: " << charCount << "\n";
	//
	//std::cout << (charCount <= maxChar) << "\n";
	//std::cout << (charCount >= minChar) << "\n";

	return ((charCount <= maxChar)&(charCount >= minChar))?1:0;
}

int main()
{
	const int k_size = 1000; //array size
	const int k_sumResult = 2020;
	
	std::string keyInput[k_size];
	int index_0[k_size];
	int index_1[k_size];

	char char_index_0[k_size];
	char char_index_1[k_size];

    std::ifstream f_inFile;
	f_inFile.open("input.txt", ios::in);

	int correctCount = 0;
	for (int i = 0; i < k_size; i++)
	{
		std::string tmp_keyChar;
		std::string key;
		std::string tmp_minChar;
		std::string tmp_maxChar;

		getline(f_inFile, tmp_minChar,'-');
		getline(f_inFile, tmp_maxChar,' ');
		index_0[i] = std::stoi(tmp_minChar);
		index_1[i] = std::stoi(tmp_maxChar);

		getline(f_inFile, tmp_keyChar,':');
		getline(f_inFile, key,'\n');	
		char* tmpCharArray = &key[0];
		char c_keyChar = tmp_keyChar[0];

		char_index_0[i] = tmpCharArray[index_0[i]];
		char_index_1[i] = tmpCharArray[index_1[i]];

		// std::cout << c_keyChar << "\n";
		// std::cout << index_0[i] << "\n";
		// std::cout << index_1[i] << "\n";
		// std::cout << char_index_0[i] << "\n";
		// std::cout << char_index_1[i] << "\n";

		// std::cout << (( c_keyChar == char_index_0[i] )|( c_keyChar == char_index_1[i])) << "\n";
		// std::cout << ( char_index_0[i] == char_index_0[i]) << "\n";

		if( ( c_keyChar == char_index_0[i] )|( c_keyChar == char_index_1[i]) )
		{
			if(char_index_0[i] != char_index_1[i])
			{
				correctCount++;
			}
		}
	}
	
	//std::getline(my_file, x);
	//std::cout << "Read Complete\n";

	

	std::cout << "Number Correct:" << correctCount << "\n";


	return 0;
}


int Partone()
{
	const int k_size = 1000; //array size
	const int k_sumResult = 2020;
	
	
	int min_char[k_size];
	int max_char[k_size];

	std::string keyChar[k_size];
	std::string key[k_size];


	int count = 0;

    std::ifstream f_inFile;
	f_inFile.open("input.txt", ios::in);

	for (int i = 0; i < k_size; i++)
	{
		std::string tmp_minChar;
		std::string tmp_maxChar;


		getline(f_inFile, tmp_minChar,'-');
		getline(f_inFile, tmp_maxChar,' ');
		getline(f_inFile, keyChar[i],':');
		getline(f_inFile, key[i],'\n');

		min_char[i] = std::stoi(tmp_minChar);
		max_char[i] = std::stoi(tmp_maxChar);	
	}
	
	//std::getline(my_file, x);
	std::cout << "Read Complete\n";

	int correctCount = 0;
	for (int i = 0; i < k_size; i++)
	{
		int result = countCharInString(keyChar[i], min_char[i], max_char[i], key[i]);
		if(result)
		{
			correctCount++;
		}
	}

	std::cout << "Number Correct:" << correctCount << "\n";


	return 0;
}
