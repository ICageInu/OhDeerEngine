#include "MainGame.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "PlayerComponent.h"
#include "Commands.h"
#include "CollisionComponent.h"
#include <SDL.h>
#include "LevelParser.h"
#include "Factory.h"

void MainGame::LoadGame() const
{
	//so basically
	//I want this to add the scene that I make, set active scene and that it
	//shouldn't be too difficult now should it
	using namespace OhDeerEngine;

	// tell the resource manager where he can find the game data
	//ResourceManager::GetInstance().Init("../Resources/");
	ResourceManager::GetInstance().Init("./Resources/");



	//SafeDelete(pPlayer);
	Factory factory;
	//auto pPlayer = new GameObject();
	float width, height;
	glm::vec2 playerPos;
	LevelParser parser;
	parser.ParseFile("./Resources/levels.txt", playerPos, width, height);

	auto pPlayer = factory.MakePlayer(playerPos, width, height);
	SceneManager::GetInstance().GetActiveScene()->Add(pPlayer);

	//do UI stuff
	auto temp = new GameObject({ ServiceLocator::GetGameHandlers()->windowDimensions.x - 100,0 });
	auto pScore = new TextComponent("0000", OhDeerEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 48));
	temp->AddComponent(pScore);
	SceneManager::GetInstance().GetActiveScene()->Subject->Objects.push_back(temp);
	SceneManager::GetInstance().GetActiveScene()->Subject->RegisterObserver(new ScoreObserver(pScore));

}
