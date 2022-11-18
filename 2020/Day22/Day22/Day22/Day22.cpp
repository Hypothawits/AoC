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

#define test 0

#if test
	#define k_inputLines 13 // test
#else
	#define k_inputLines 53 // input
#endif

struct listPair
{
	list<uint16_t> p1;
	list<uint16_t> p2;
};

// function to flip line
void flipTileChars(char* input)
{
	char temp[10];
	for (auto i = 0; i < 10; i++)
	{
		temp[i] = input[i];
	}

	int rev = 9;
	for (auto i = 0; i < 10; i++)
	{
		input[i] = temp[rev];
		rev--;
	}
}

bool compareChars(char* x, char* y)
{
	for (auto i = 0; i < 10; i++)
	{
		if (y[i] != x[i]) { return false; }
	}
	return true;
}

void copyChar(char* in, char* out)
{
	for (auto i = 0; i < 10; i++)
	{
		out[i] = in[i];
	}
}

bool compareList(list <uint16_t> a, list <uint16_t> b);

bool checkPlayRecord(vector<listPair>& playrecord, list<uint16_t>& p1_deck, list<uint16_t>& p2_deck);

void playRound(list<uint16_t>&p1_deck, list<uint16_t>&p2_deck);
void playRound_Rec(list<uint16_t>& p1_deck, list<uint16_t>& p2_deck, int& level);

int playGame(list<uint16_t>&p1_deck, list<uint16_t>&p2_deck, int& level);
int playGame_top(list<uint16_t>&p1_deck, list<uint16_t>&p2_deck);

uint64_t countScore(list<uint16_t>deck);


int  ctoi(char x) { return uint64_t(x - 48); }
char itoc(int x)  { return     char(x + 48); }
//int = char - 48

uint16_t newFuction(list<uint16_t>& p1_deck, list<uint16_t>& p2_deck);

int main()
{
	//Start testing
	list <uint16_t> a = {1,2,3,4,5,6,7,8,9};
	list <uint16_t> b = { 1,2,3,4,5,6,7,8,9 };
	auto testT = compareList(a, b);

	list <uint16_t> c = { 1,2,3,99,5,6,7,8,9 };
	list <uint16_t> d = { 1,2,3,9,5,6,7,8,4 };
	auto testF = compareList(a, c);
	
	list <uint16_t> et;
	auto after = et.size();

	vector<listPair> test_playrecord;

	auto checkF = (a == a);
	auto checkf	= (d == a);
	auto checkT	= (c == a);
	//end testing

	auto t1 = std::chrono::high_resolution_clock::now();

	std::vector<string>inputLines;
	inputLines.resize(k_inputLines);

	list<uint16_t>p1_deck;
	list<uint16_t>p2_deck;
	//auto t1 = std::chrono::high_resolution_clock::now();


	std::ifstream f_inFile;

	#if test
		f_inFile.open("test.txt", ios::in);
	#else
		f_inFile.open("input.txt", ios::in);
	#endif
	
	for (int i = 0; i < k_inputLines; i++)
	{
		//std::string in;
		getline(f_inFile, inputLines[i]);

	}

	// Read the value ranges
	int playerNum = 0;
	for (auto line : inputLines)
	{
		if (line[0] == 'P')
		{
			playerNum += 1;
		}
		else if(line[0] != 0)
		{	// not a new player
			// add card number to player deck
			int tempValue = 0;

			#pragma warning(suppress : 4996)
			sscanf(&line[0], "%d", &tempValue);

			switch (playerNum)
			{
			case 1:
				// player 1
				p1_deck.push_back(tempValue);
				break;
			case 2:
				// player 2
				p2_deck.push_back(tempValue);
				break;
			default:
				break;
			}
		}
	}

	// Part 1
	/*while ((p1_deck.size() != 0) && (p2_deck.size() != 0))
	{
		playRound(p1_deck, p2_deck);
	}

	auto p1_score = countScore(p1_deck);
	auto p2_score = countScore(p2_deck);*/

	// Part 2

	//vector <listPair> g_playrecord;
	int level = -1;
	//auto winner = playGame(p1_deck, p2_deck, level);
	
	auto winner = newFuction(p1_deck, p2_deck);


	auto p1_score = countScore(p1_deck);
	auto p2_score = countScore(p2_deck);

	// test = 291

	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	cout << "p1 Score: " << p1_score << "\n";
	cout << "p2 Score: " << p2_score << "\n";
	cout << "\n\n\n";
	cout << "Finished in: " << duration << " microseconds\n\n";
	return 0;
	
}

void giveWinnerCards(list<uint16_t>& p1_deck, list<uint16_t>& p2_deck, uint16_t p1_card, uint16_t p2_card, uint16_t winner)
{
	switch (winner)
	{
	case 1:
		p1_deck.push_back(p1_card);
		p1_deck.push_back(p2_card);
		break;
	case 2:
		p2_deck.push_back(p2_card);
		p2_deck.push_back(p1_card);
		break;
	default:
		cout << "ERROR: non player won?!" << endl;
		break;
	}
}

bool checkNumCardsRemaining(list<uint16_t>& p1_deck, list<uint16_t>& p2_deck, uint16_t p1_card, uint16_t p2_card)
{
	auto p1_deckSize = p1_deck.size();
	auto p2_deckSize = p2_deck.size();

	auto p1_test = (p1_card <= p1_deckSize);
	auto p2_test = (p2_card <= p2_deckSize);

	return (p1_test && p2_test);
}

uint16_t playNormalGame(uint16_t p1_card, uint16_t p2_card)
{
	return (p1_card >= p2_card) ? 1 : 2;
}

bool doDecksMatch(list<uint16_t> a, list<uint16_t> b)
{
	return a == b;
}

bool haveDecksBeenPlayedBefore(list<uint16_t>& p1_deck, list<uint16_t>& p2_deck, vector<listPair>& recordOfPastDecks)
{
	// loop over record of past decks
	for (auto pair = 0; pair < recordOfPastDecks.size(); pair++)
	{
		auto p1_checkVal = recordOfPastDecks[pair].p1;
		auto p2_checkVal = recordOfPastDecks[pair].p2;

		// does p1_checkVal match with the current p1_deck?
		auto p1_test = (p1_deck == p1_checkVal);
		auto p2_test = (p2_deck == p2_checkVal);

		if (p1_test && p2_test) { return true; }
	}

	// No match has been found
	// create a new list pair to store the current decks
	listPair newPair;
	// resize to hold the current decks
	newPair.p1.resize(p1_deck.size());
	newPair.p2.resize(p2_deck.size());

	// copy the current deck into the new record entery
	std::copy(p1_deck.begin(), p1_deck.end(), newPair.p1.begin());
	std::copy(p2_deck.begin(), p2_deck.end(), newPair.p2.begin());

	// add the record entery to the vector
	recordOfPastDecks.push_back(newPair);

	// return that no match was found
	return false;
	
}

uint16_t newFuction(list<uint16_t>& p1_deck, list<uint16_t>& p2_deck)
{
	// create a list of past decks for this current game
	vector <listPair> recordOfPastDecks;

	// While the deck still have cards in them
	uint16_t winner = 0;
	while ( (p1_deck.size() != 0) && (p2_deck.size() != 0) )
	{
		// check if current decks have been played before
		auto checkPlayedBefore = haveDecksBeenPlayedBefore(p1_deck, p2_deck, recordOfPastDecks);
		if (checkPlayedBefore)
		{
			uint16_t winner = 1;
			return winner;
		}
		else {

		}

		auto p1_card = p1_deck.front();	// Get cards from deck
		auto p2_card = p2_deck.front();
		p1_deck.pop_front();			// Remove cards from deck
		p2_deck.pop_front();

		// Draw top two cards
		// if you havent played this deck before 
			

		// check if number of remaining cards in decks is more than card value
		auto doRecursion = checkNumCardsRemaining(p1_deck, p2_deck, p1_card, p2_card);

		if (doRecursion)
		{
			// if more than card, go into recursion
			// with a copy of the decks but only include up to the 'card value' number of cards 
			auto p1_newDeckSize = p1_card; // does nothing, just to relable
			auto p2_newDeckSize = p2_card; // does nothing, just to relable

			std::list<uint16_t> p1_newDeck_Copy(p1_deck.begin(), std::next(p1_deck.begin(), p1_newDeckSize));
			std::list<uint16_t> p2_newDeck_Copy(p2_deck.begin(), std::next(p2_deck.begin(), p2_newDeckSize));

			winner = newFuction(p1_newDeck_Copy, p2_newDeck_Copy);

			// give the winner the cards
			// giveWinnerCards(p1_deck, p2_deck, p1_card, p2_card, winner);
		}
		else
		{
			winner = playNormalGame(p1_card, p2_card);
			// else: play a normal round
				// winner is highest card
				// winner card is added to their deck first and then the losing card

			//giveWinnerCards(p1_deck, p2_deck, p1_card, p2_card, winner);
		}

		giveWinnerCards(p1_deck, p2_deck, p1_card, p2_card, winner);


	}

	if (winner == 0)
	{
		winner = (p1_deck.size() != 0) ? 1 : 2;
	}

	// return the winner 
	return winner;
}











void playRound(list<uint16_t>&p1_deck, list<uint16_t>&p2_deck)
{
	// play the top card
	auto p1_card = p1_deck.front();
	auto p2_card = p2_deck.front();
	p1_deck.pop_front();
	p2_deck.pop_front();

	// compare and find winner

	int whoWon = (p1_card >= p2_card) ? 1 : 2;

	switch (whoWon)
	{
	case 1:
		p1_deck.push_back(p1_card);
		p1_deck.push_back(p2_card);
		break;
	case 2:
		p2_deck.push_back(p2_card);
		p2_deck.push_back(p1_card);
		break;
	default:
		cout << "ERROR: non player won?!" << endl;
		break;
	}

}

bool compareList(list <uint16_t> a, list <uint16_t> b)
{
	if (a.size() == b.size())
	{
		return std::equal(a.begin(), a.end(), b.begin());
	}
	else
	{
		return false;
	}
}

bool checkPlayRecord(vector<listPair>& playrecord, list<uint16_t>& p1_deck, list<uint16_t>& p2_deck)
{
	bool found = false;
	for (auto i = 0; i < playrecord.size(); i++)
	{
		auto p1_test = compareList(playrecord[i].p1, p1_deck);
		auto p2_test = compareList(playrecord[i].p2, p2_deck);

		if (p1_test && p2_test)
		{
			return true;
		}
	}

	if (!found)
	{	// not found, add to the record
		listPair newPair;
		newPair.p1.resize( p1_deck.size() );
		newPair.p2.resize( p2_deck.size() );

		std::copy(p1_deck.begin(), p1_deck.end(), newPair.p1.begin());
		std::copy(p2_deck.begin(), p2_deck.end(), newPair.p2.begin());

		playrecord.push_back(newPair);
		return false;
	}
}

//int playGame_top(list<uint16_t>&p1_deck, list<uint16_t>&p2_deck)
//{
//	//vector<pair_> playrecord;
//	vector <listPair> playrecord;
//	while ((p1_deck.size() != 0) && (p2_deck.size() != 0))
//	{
//		// check if current deck has been had before!
//		// this is wrong, must be same cards in same order
//		// cange playRrecord to vector<list<uint16_t>> and update checkPlayRecord()
//		// UGH
//		const auto playedB4 = checkPlayRecord(playrecord, p1_deck, p2_deck);
//
//		if (!playedB4)
//		{
//			// play the round
//			playRound_Rec(p1_deck, p2_deck);
//			
//		}
//		else
//		{	// p1 wins
//			return 1;
//		}
//
//	}
//
//
//	// who won?
//	const int winner = (p1_deck.size() != 0) ? 1 : 2;
//
//	return winner;
//}

int playGame(list<uint16_t> &p1_deck, list<uint16_t> &p2_deck, int & level)
{
	level++;
	//vector<pair_> playrecord;
	vector <listPair> playrecord;
	while ((p1_deck.size() != 0) && (p2_deck.size() != 0))
	{
		// check if current deck has been had before!
		// this is wrong, must be same cards in same order
		// cange playRrecord to vector<list<uint16_t>> and update checkPlayRecord()
		// UGH
		const auto playedB4 = checkPlayRecord(playrecord, p1_deck, p2_deck);

		if (!playedB4)
		{
			// play the round
			playRound_Rec(p1_deck, p2_deck, level);
		}
		else
		{	// p1 wins
			return 1;
		}

		if (level == 0)
		{
			cout << '.' << endl;
		}

	}

	

	// who won?
	const int winner = (p1_deck.size() != 0) ? 1 : 2;
	level--;
	return winner;
}



void playRound_Rec(list<uint16_t>& p1_deck, list<uint16_t>& p2_deck, int& level)
{
	// play the top card
	auto p1_card = p1_deck.front();
	auto p2_card = p2_deck.front();
	p1_deck.pop_front();
	p2_deck.pop_front();

	// size of deck
	auto p1_deckSize = p1_deck.size();
	auto p2_deckSize = p2_deck.size();

	// if both deckSize >= value of card drawn
	//		enter recrsion
	int whoWon = 0;
	if ((p1_card <= p1_deckSize) && (p2_card <= p2_deckSize))
	{
		// Create new deck copies
		std::list<uint16_t> p1_newDeckCopy(p1_deck.begin(), std::next(p1_deck.begin(), p1_card));
		std::list<uint16_t> p2_newDeckCopy(p2_deck.begin(), std::next(p2_deck.begin(), p2_card));
		// Start new recursive game
		whoWon = playGame(p1_newDeckCopy, p2_newDeckCopy, level);
	}
	else
	{
		// compare and find winner
		whoWon = (p1_card > p2_card) ? 1 : 2;
	}

	switch (whoWon)
	{
	case 1:
		p1_deck.push_back(p1_card);
		p1_deck.push_back(p2_card);
		break;
	case 2:
		p2_deck.push_back(p2_card);
		p2_deck.push_back(p1_card);
		break;
	default:
		cout << "ERROR: non player won?!" << endl;
		break;
	}

}



uint64_t countScore(list<uint16_t>deck)
{
	const auto size = deck.size();
	uint64_t result = 0;
	uint64_t i = 1;
	while (deck.size() != 0)
	{
		result += i * deck.back();
		deck.pop_back();
		i++;
	}
	return result;
}