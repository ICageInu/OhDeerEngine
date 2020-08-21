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
#include "Subject.h"
#include <array>

void MainGame::LoadGame() const
{
	//so basically
	//I want this to add the scene that I make, set active scene and that it
	//shouldn't be too difficult now should it
	using namespace OhDeerEngine;

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("./Resources/");



	//SafeDelete(pPlayer);
	Factory factory;
	//auto pPlayer = new GameObject();
	float width, height;
	glm::vec2 playerPos;

	//{
	//	//debug level
	//	auto test = SceneManager::GetInstance().CreateScene("debug");
	//	auto player = factory.MakePlayer({150,150}, 30, 30);
	//	auto emerald = factory.MakeEmerald({ 250,250 }, 30, 30);
	//	test->Add(emerald);
	//	test->Add(player);
	//}



	LevelParser parser;
	parser.ParseFile("./Resources/levels.txt", playerPos, width, height);
	
	for (size_t i = 1; i < SceneManager::GetInstance().GetScenes().size(); i++)
	{
		auto pPlayer = factory.MakePlayer(playerPos, width, height);
		SceneManager::GetInstance().GetScene(i)->Add(pPlayer);
	}
	//do UI stuff
	//right now this is crashing (memory leaks) cause it gets added to the observer
	//but it doesn't get added to the active scene
	auto temp = new GameObject({ ServiceLocator::GetGameHandlers()->windowDimensions.x - 100,0 });
	auto pScore = new TextComponent("0000", OhDeerEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 48));
	temp->AddComponent(pScore);
	SceneManager::GetInstance().GetScene(1)->Subject->Objects.push_back(temp);
	SceneManager::GetInstance().GetScene(1)->Subject->RegisterObserver(new ScoreObserver(pScore));
	//TODO fix health cause brain is fried right now and please don't preprogram this
	
	std::array<RenderComponent*, 5> temparray;
	for (size_t i = 0; i < temparray.size(); i++)
	{
		temp = new GameObject({ width * i,0 });
		auto pPlayerTexture = new OhDeerEngine::RenderComponent();
		pPlayerTexture->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("digger.png"), (int)width, (int)height);
		temp->AddComponent(pPlayerTexture);
		SceneManager::GetInstance().GetScene(1)->Subject->Objects.push_back(temp);
		if (i > 2)temp->IsActive = false;
		temparray[i] = pPlayerTexture;
	}
	
	SceneManager::GetInstance().GetScene(1)->Subject->RegisterObserver(new HealthObserver(temparray));



	//setting up the main menu
	//will be at pos 0
	SceneManager::GetInstance().GetScene("0");
	factory.MakeStartScreen(SceneManager::GetInstance().GetScene("0"));
}
