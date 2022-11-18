// Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
using namespace std;

// vibrant lavender bags contain 1 shiny coral bag, 4 dotted purple bags.
// [holder_name] bags contain [#] [name] bag(s), [#] [name] bag(s).

struct BAG
{
	int id;
	std::string name;
	std::vector<BAG*> heldBagList; //List of bags that are held.
	bool haveOpened = 0;
};

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

int countGoldBags_old(BAG &currentBag, int &count)
{
	std::cout << "Bag: " << currentBag.name << "\n";
	//check if opened
	if(currentBag.haveOpened == 1)
	{
		std::cout << "have visited = true\n";
		return count;
	}
	else
	{
		std::cout << "new bag open!\n";
		//set the have opened check
		currentBag.haveOpened = 1;
		
		count++;
		for(int i = 0; i < currentBag.heldBagList.size(); i++)
		{
			countGoldBags_old(*currentBag.heldBagList[i], count);
		}
		std::cout << "count: " << count << "\n";
		return count;
	}

	return -1;

}

int main()
{
	const int k_size = 594; //array Length
	std::string input[k_size];

    std::ifstream f_inFile;
	f_inFile.open("input.txt", ios::in);

	for (int i = 0; i < k_size; i++)
	{
		getline(f_inFile, input[i]);
		
	}
	std::cout << "Read Complete\n";

	// extract list of unique bag names
	std::string hold_delimiter = "bags";
	std::vector<std::string> bagNamesFound;//store unique bagnames
	for (int i = 0; i < k_size; i++)
	{
		std::string s_holdBag = input[i].substr(0, input[i].find(hold_delimiter) );
		bagNamesFound.push_back(s_holdBag);
	}

	std::cout << "Finished counting bags and " << "found:" << bagNamesFound.size() << " Bag Names! \n";

	// Create list of BAGS type 
	std::vector<BAG> bags; // What bags go in other bags
	for (int i = 0; i < k_size; i++)
	{
		BAG newBag;
		newBag.id = i;
		newBag.name = bagNamesFound[i];
		bags.push_back(newBag);
	}
	std::cout << "Finished creating bags and " << "made :" << bags.size() << " Bags! \n";

	// Go through bags and add the values to list
	
	////////
	// vibrant lavender bags contain 1 shiny coral bag, 4 dotted purple bags.
	// [hold_Bag] bags contain [#] [name] bag(s), [#] [name] bag(s).

	for (int holdBagIndex = 0; holdBagIndex < k_size; holdBagIndex++) // change from k_size!
	{
		std::string in = input[holdBagIndex];
		string::iterator it;
		// int j = 0;
		for(it = in.begin() ; it < in.end(); it++)
		{
			
			bool x = isNumber(*it);
			bool foundBag = false;
			if(x)
			{	// it's a number
				// exstract the bag name
				size_t s_pos = (it - in.begin())+2; // get number pos realitive to start
				size_t f_pos = in.find("bag", s_pos);
				std::string heldBagName = in.substr(s_pos, f_pos-s_pos); // +2 for num and space :

				int numberOfHeldBags = char(*it)-48;
				int heldBagIndex = 0;

				//need to convert from string to idex for the held bag
				for(int j = 0; j < k_size; j++)
				{	// Check every bag name to find index of held bag
					if( heldBagName.compare(bags[j].name) == 0 )
					{	// compare held name to name of each bag in the bags vector
						heldBagIndex = j;
						break;
					}
				}

				// Add a ref j times (as many as fit in the bag)
				for(int j = 0; j < numberOfHeldBags; j++)
				{
					bags[holdBagIndex].heldBagList.push_back(&bags[heldBagIndex]);
				}
			}
		}
	}
	
	// Create list of bags
	std::vector<BAG> bags2; // Where bags can go
	for (int i = 0; i < k_size; i++)
	{	// Make vector of all bag types
		BAG newBag;
		newBag.id = i;
		newBag.name = bagNamesFound[i];
		bags2.push_back(newBag);
	}

	// Get where bags could be held
	for (int i = 0; i < k_size; i++)
	{
		BAG x = bags[i]; //get bag from vector
		// x 
		int numInBag = x.heldBagList.size();
		int prevID = -1;
		for (int j = 0; j < numInBag; j++)
		{
			int currentID = x.heldBagList[j]->id;
			if (prevID != currentID)
			{	// new bag
				prevID = currentID;
				bags2[currentID].heldBagList.push_back(&bags2[i]);
				// the list of of bags that Bags2 could be in has Bags_i added to it (bags2[i] matching index numbers)
			}
		}
	}

	// Search for shiny gold bags (index 275-1)
	BAG goldShinyBag = bags2[275-1];
	std::cout << " -------- \n";
	std::cout << goldShinyBag.name << "\n";
	std::cout << goldShinyBag.heldBagList[0]->name << ".\n";
	std::cout << goldShinyBag.heldBagList[1]->name << ".\n";
	std::cout << goldShinyBag.heldBagList[2]->name << ".\n";
	std::cout << goldShinyBag.heldBagList[3]->name << ".\n";
	std::cout << goldShinyBag.heldBagList[4]->name << ".\n";

// shiny gold
// muted crimson .
// dim red .
// muted fuchsia .
// mirrored plum .
// wavy purple .

	std::cout << " -------- \n";



	int count = 0;
	int out = countGoldBags(bags2, (275-1), count);
	std::cout << "Count: " << count << "\n"; 

	// std::cout << input[0] << "\n";
	// std::cout << "\n\n\nbag 0 id " << bags[0].id << "\n";
	// std::cout << "bag 0 name "  << bags[0].name << "\n";
	// std::cout << "bag 0 holds " << bags[0].heldBagList[0]->name << "\n";
	// std::cout << "bag 0 holds " << bags[0].heldBagList[0]->heldBagList[0]->name << "\n";
	
	// std::cout << "bags2 name:" << bags2[496-1].name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[0]->name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[1]->name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[2]->name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[3]->name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[4]->name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[5]->name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[6]->name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[7]->name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[8]->name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[9]->name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[10]->name << "\n";
	// std::cout << "it can contain: " << bags2[496-1].heldBagList[11]->name << "\n";
	


 	std::cout << "\n\n\n";
	return 0;

}

