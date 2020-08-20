#pragma once
#include "OhDeerPCH.h"
#include <fstream>
#include <regex>
#include "GameObject.h"
#include "glm/common.hpp"
#include "Scene.h"
#include "SceneManager.h"
#include <SDL.h>
#include "Factory.h"
class LevelParser
{
public:
	inline void ParseFile(const std::string& fileName, glm::vec2& playerPos, float& playerWidth, float& playerHeight)
	{
		Factory factory;
		int objWidth, screenWidth;
		int objHeight, screenHeight;
		int amountRows = 15;
		int amountColums = 11;
		SDL_GetWindowSize(OhDeerEngine::ServiceLocator::GetGameHandlers()->window, &screenWidth, &screenHeight);
		objWidth = screenWidth / amountRows + 1; //adding one pixel to width and height to make sure there are no seams because of floating errors
		objHeight = screenHeight / amountColums + 1;
		std::ifstream file;
		std::string line;
		std::regex sentence{ "^\\D+[SBHVC\\s]{15}.+" };
		std::string firstChar;
		file.open(fileName, std::ios::in);
		int level{ 0 };
		int vertCounter{ 42 };
		auto pScene = OhDeerEngine::SceneManager::GetInstance().CreateScene(std::to_string(level));

		//setting player pos and width
		playerPos = { screenWidth / 2.0f, screenHeight - (float)objHeight };
		playerWidth = (float)objWidth;
		playerHeight = (float)objHeight;


		if (file.is_open())
		{
			while (!file.eof())
			{
				//so only wanna make new scene if the shenanigans is stopped parsing one level, but I need to be able to keep a reference to one level
				std::getline(file, line);
				firstChar = line.substr(0, line.find("\""));
				if (line[0] == '{' || line[0] == ' ' && line[1] == '{')
				{
					level++;
					pScene = OhDeerEngine::SceneManager::GetInstance().CreateScene(std::to_string(level));

					pScene->Add(factory.MakeFPS());
					vertCounter = { 1 };
					line = line.substr(1);
				}

				if (regex_match(line, sentence))
				{
					int horzCounter{ 0 };
					size_t firsPos = line.find('\"') + 1;
					line = line.substr(firsPos, line.find((char)firsPos, '\"'));
					line = line.substr(0, line.find('\"'));
					do
					{
						switch (line[0])
						{
						case ' ':
							factory.MakeLevel(pScene, { objWidth * horzCounter,objHeight * vertCounter
								}, (float)objWidth, (float)objHeight);
							horzCounter++;
							break;
						case 'B':
							factory.MakeLevel(pScene, { objWidth * horzCounter,objHeight * vertCounter
								}, (float)objWidth, (float)objHeight);
							pScene->Add(factory.MakeMoneyBag({ objWidth * horzCounter,objHeight * vertCounter
								}, (float)objWidth, (float)objHeight));
							horzCounter++;
							break;
						case 'H':
							//pScene->Add(factory.MakeTunnel({ screenWidth * horzCounter, screenHeight * vertCounter
							//	},"HorzTunnel.png", (float)screenWidth, (float)screenHeight));
						//horzCounter++;
						//	break;						
						case 'V':
							//pScene->Add(factory.MakeTunnel({ screenWidth * horzCounter, screenHeight * vertCounter
							//	}, "VertTunnel.png", (float)screenWidth, (float)screenHeight));
							horzCounter++;
							break;
						case 'C':
							factory.MakeLevel(pScene,{ objWidth * horzCounter,objHeight * vertCounter
								}, (float)objWidth, (float)objHeight);
							pScene->Add(factory.MakeEmerald({ objWidth * horzCounter,objHeight * vertCounter
								}, (float)objWidth, (float)objHeight));
							horzCounter++;
							break;
						case 'S':
							pScene->Add(factory.MakeEnemyStart({ screenWidth - screenWidth * horzCounter,screenHeight - screenHeight * vertCounter
								}, (float)screenWidth, (float)screenHeight));
							horzCounter++;
							break;
						}

						line = line.substr(1);
					} while (horzCounter < amountRows);
					vertCounter++;
				}

			}
		}
		file.close();

	}
};
