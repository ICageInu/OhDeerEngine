#include "MainGame.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"

void MainGame::LoadGame() const
{
	//so basically
	//I want this to add the scene that I make, set active scene and that it
	//shouldn't be too difficult now should it
	using namespace OhDeerEngine;

	// tell the resource manager where he can find the game data
	//ResourceManager::GetInstance().Init("../Resources/");
	ResourceManager::GetInstance().Init("./Resources/");


	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = new GameObject();
	//go->SetTexture("background.jpg");
	auto tex1 = new RenderComponent();
	tex1->AddTexture(ResourceManager::GetInstance().LoadTexture("background.jpg"));
	go->AddComponent(tex1);
	go->SetTag("background");
	scene.Add(go);

	go = new GameObject({ 216, 180 }, 0);
	////go->SetTexture("logo.png");
	auto tex2 = new RenderComponent();
	tex2->AddTexture(ResourceManager::GetInstance().LoadTexture("logo.png"));
	go->AddComponent(tex2);
	scene.Add(go);

	go = new GameObject({ 20,20 });
	auto tex3 = new RenderComponent();
	tex3->AddTexture(ResourceManager::GetInstance().LoadTexture("logo.png"));
	auto font = new TextComponent("Programming 4 Assignment");
	font->AddFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));

	go->AddComponent(font);
	go->AddComponent(tex3);
	scene.Add(go);
}
