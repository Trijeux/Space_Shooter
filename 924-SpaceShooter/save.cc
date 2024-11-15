#include "save.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void Save::Load(std::vector<int>& players)
{
	if (std::ifstream infile(kDataFilePath); infile.is_open())
	{
		int number;
		while (infile >> number) {
			players.push_back(number);
		}
		infile.close();
	}
	else
	{
		std::cerr << "Unable to open file!" << std::endl;
	}

	std::ranges::sort(players, std::greater<int>());  // NOLINT(modernize-use-transparent-functors)
}


void Save::SaveGame(std::vector<int>& players)
{
	if (std::ofstream outfile(kDataFilePath); outfile.is_open())
	{
		std::ranges::sort(players, std::greater<int>());   // NOLINT(modernize-use-transparent-functors)

		int number_of_score = 0;

		for (const int score : players) {
			outfile << score << "\n";
			number_of_score++;
			if (number_of_score >= 10)
			{
				break;
			}
		}
		outfile.close();
	}
	else
	{
		std::cerr << "Unable to open file!" << std::endl;
	}
}
