#pragma once
#include "OhDeerPCH.h"
#include <fstream>
#include <array>
#include <string>
class Highscore
{
public:
	inline void ParseFile(const std::string& filePath, std::array<std::string, 10>& highscores,
		std::array<std::string, 10>& names)
	{
		std::ifstream file;
		std::string line;
		file.open(filePath, std::ios::in);
		size_t i{ 0 },j{ 0 };
		if (file.is_open())
		{
			while (!file.eof())
			{
				std::getline(file, line);

				if (i % 2)
				{
					names[j] = line;
					j++;
				}

				else highscores[j] = line;

				i++;
			}
			file.close();
		}
	}

	inline void SaveHighscore()
	{

	}
};