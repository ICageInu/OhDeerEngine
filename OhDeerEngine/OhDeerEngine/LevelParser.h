#pragma once
#include <fstream>
#include <regex>
#include "GameObject.h"
#include "glm/common.hpp"
#include "Scene.h"
#include "SceneManager.h"

class LevelParser
{
public:
	inline void ParseFile(const std::string& fileName)
	{
		//local vectors
		//then when faces assemble vertexs 
		//then when returning vertexes check if vertex is in there already
		//if not new vertex, if it is index is old vertex
		std::ifstream file;
		std::string line;
		std::vector <glm::vec2> leftBottom;
		std::regex sentence{ "^\\D+[SBHVC\\s]{15}.+" };
		std::regex start{ "[S|s]" };
		std::regex wall{ "\\s" };
		std::regex horzTunnel{ "[H|h]" };
		std::regex vertTunnel{ "[V|v]" };
		std::regex moneyBag{ "[B|b]" };
		std::regex emerald{ "[C|c]" };
		std::string firstChar;
		file.open(fileName, std::ios::in);
		int level{ 1 };
		auto& pScene = OhDeerEngine::SceneManager::GetInstance().CreateScene(std::to_string(level));

		if (file.is_open())
		{
			while (!file.eof())
			{
				//so only wanna make new scene if the shenanigans is stopped parsing one level, but I need to be able to keep a reference to one level
				std::getline(file, line);
				firstChar = line.substr(0, line.find("\""));
				if (line[0] == '{')
				{
					line = line.substr(1);
				}

				if (regex_match(line, sentence))
				{
					line = line.substr(1);
					if (line[0] == '"')line = line.substr(1);
					


					line = line.substr(line.find(' ') + 1);
					float yCoord{ std::stof(line.substr(0, line.find(' '))) };
					line = line.substr(line.find(' ') + 1);
					float zCoord{ std::stof(line.substr(0)) };
					//vert.push_back(Elite::FPoint3{ xCoord, yCoord, zCoord });
				}

			}
		}
		file.close();

	}
};
