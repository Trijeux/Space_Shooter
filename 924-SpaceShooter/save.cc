#include "save.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void Save::Load(std::vector<int>& players)
{
	std::ifstream infile(kDataFilePath);

	if (infile.is_open())
	{
		int number;
		while (infile >> number) {  // Lecture de chaque entier dans le fichier
			players.push_back(number);
		}
		infile.close();
	}
	else
	{
		std::cerr << "Unable to open file!" << std::endl;
	}

	std::ranges::sort(players, std::greater<int>());
}


void Save::SaveGame(std::vector<int>& players)
{
	std::ofstream outfile(kDataFilePath);  // Ouvrir en mode écriture (sans append)

	if (outfile.is_open())
	{
		std::ranges::sort(players, std::greater<int>());  // Tri des scores en ordre décroissant

		int number_of_score = 0;

		for (int score : players) {
			outfile << score << "\n";  // Écriture de chaque score sur une nouvelle ligne
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
