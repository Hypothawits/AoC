#pragma once
constexpr bool debug = false;

void openFile(std::ifstream& f_inFile, bool debug)
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
