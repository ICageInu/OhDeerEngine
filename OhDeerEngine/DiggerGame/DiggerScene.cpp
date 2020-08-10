#include "DiggerScene.h"
#include "SceneManager.h"
#include "Singleton.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"

DiggerScene::DiggerScene(const std::string& sceneName):
	Scene(sceneName)
{
	//OhDeerEngine::SceneManager::GetInstance().CreateScene(sceneName);
}

void DiggerScene::Initialize()
{
	using namespace OhDeerEngine;

	auto go = new GameObject();
	//go->SetTexture("background.jpg");
	auto tex1 = new RenderComponent();
	tex1->AddTexture(ResourceManager::GetInstance().LoadTexture("background.jpg"));
	go->AddComponent(tex1);
	go->SetTag("background");
	Add(go);

	go = new GameObject({ 216, 180 }, 0);
	////go->SetTexture("logo.png");
	auto tex2 = new RenderComponent();
	tex2->AddTexture(ResourceManager::GetInstance().LoadTexture("logo.png"));
	go->AddComponent(tex2);
	Add(go);

	go = new GameObject({ 60,60 });
	auto tex3 = new RenderComponent();
	tex3->AddTexture(ResourceManager::GetInstance().LoadTexture("logo.png"));
	auto font = new TextComponent("Programming 4 Assignment");
	font->AddFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	

	go->AddComponent(font);
	go->AddComponent(tex3);
	Add(go);


	m_pFPSCounter = new GameObject({ 20,20 });
	auto font2 = new TextComponent("Programming 4 Assignment");
	font2->AddFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	m_pFPSCounter->AddComponent(font2);
	Add(m_pFPSCounter);
}

void DiggerScene::Update([[maybe_unused]]float deltaT)
{
	m_FrameCounter++;
	m_SecondsTimer += deltaT;

	if (m_SecondsTimer >= 1.f)
	{
		m_pFPSCounter->GetComponent<OhDeerEngine::TextComponent>()->SetText(std::to_string(m_FrameCounter));
		m_SecondsTimer -= 1.f;
		m_FrameCounter = 0;

	}

}
