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




	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	//Factory factory;

	//auto go = new GameObject();
	////go->SetTexture("background.jpg");
	//auto tex1 = new RenderComponent();
	//tex1->SetTexture(ResourceManager::GetInstance().LoadTexture("background.jpg"));
	//go->AddComponent(tex1);
	//scene.Add(go);

	//go = new GameObject({ 0,0 }, 0);
	//////go->SetTexture("logo.png");
	//auto tex2 = new RenderComponent();
	//tex2->SetTexture(ResourceManager::GetInstance().LoadTexture("logo.png"));
	//go->AddComponent(tex2);
	//scene.Add(go);

	//go = new GameObject({ 60,60 });
	//auto tex3 = new RenderComponent();
	//tex3->SetTexture(ResourceManager::GetInstance().LoadTexture("logo.png"));
	//auto font = new TextComponent("Programming 4 Assignment");
	//font->AddFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	//auto fontCol = new CollisionComponent({ 0,0 },150,30,true);
	//go->AddComponent(fontCol);
	//go->SetTag("title");
	//go->AddComponent(font);
	//go->AddComponent(tex3);
	//scene.Add(go);

	//auto player = factory.MakePlayer({ 0,0 },30, 30);
	//scene.Add(player);


	//setup of enemies
	//auto pEnemOne = new GameObject({ 150,150 });
	//auto pHobbinTexture = new RenderComponent();
	//pHobbinTexture->SetTexture(ResourceManager::GetInstance().LoadTexture("hobbin.png"), 30, 30, { 0,0 }, false, false, 1, 1);
	//auto pHobbinComp = new CollisionComponent({ 150,150 },30,30,true);

	//pEnemOne->AddComponent(pHobbinTexture);
	//pEnemOne->AddComponent(pHobbinComp);
	//scene.Add(pEnemOne);

	LevelParser parser;
	parser.ParseFile("./Resources/levels.txt");



}
