#ifndef SAVE_H
#define SAVE_H
#include <string>
#include <vector>

constexpr char kDataFilePath[] = "dataGame.txt";

class Save
{
public:
	static void Load(std::vector<int>& players);
	static void SaveGame(std::vector<int>& players);
};

#endif // SAVE_H
