#pragma once
#include "OhDeerPCH.h"
#include <fstream>
#include <array>
#include <string>
class Highscore
{
public:
	inline void ParseFile(const std::string& filePath, std::array<int, 10>& highscores,
		std::array<std::string, 10>& names)
	{
		std::ifstream file;
		std::string line;
		file.open(filePath, std::ios::in);
		size_t i{ 0 }, j{ 0 };
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

				else
				{
					if (line.size() != 0)
						highscores[j] = std::stoi(line);
					else  highscores[j] = 0;
				}
				i++;
				if (j > 9) break;
			}
			file.close();
		}
	}

	inline void SaveHighscore(const std::string& filePath, int score, const std::string& initials)
	{
		std::ifstream readFile;
		std::ofstream writeFile;
		std::string line;
		readFile.open(filePath, std::ios::in);
		size_t i{ 0 }, j{ 0 };
		std::vector<std::string> names;
		std::vector<int> highscores;
		//read in values
		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				std::getline(readFile, line);

				if (i % 2)
				{
					names[j] = line;
					j++;
				}
				else
				{

					if (line.size() != 0)
						highscores[j] = std::stoi(line);
					else  highscores[j] = 0;
				}
				i++;
			}
			readFile.close();
		}

		//checking if any changes
		//first check if any open spaces

		size_t savePlace{ 90000 };
		for (size_t idx = 0; idx < highscores.size(); idx++)
		{
			if (highscores[idx] == 0)
			{
				savePlace = idx;
				break;
			}
		}

		if (savePlace != 90000)
		{
			highscores[savePlace] = score;
			names[savePlace] = initials;
		}
		else
		{
			for (size_t idx = 0; idx < highscores.size(); idx++)
			{
				if (score > highscores[idx])
				{
					highscores[savePlace] = score;
					names[savePlace] = initials;
					break;
				}
			}
		}


		//writing away
		writeFile.open(filePath, std::ios::out);
		i = { 0 }, j = { 0 };
		if (writeFile.is_open())
		{
			while (i < names.size() * 2)
			{
				if (names[j].size() == 0) break;
				if (i % 2)
				{
					writeFile << names[j] + "\n";
					j++;
				}
				else writeFile << std::to_string(highscores[j]) + "\n";
				i++;
			}
			writeFile.close();
		}
	}
};