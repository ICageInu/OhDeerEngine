#include "TestScene.h"
#include "CubePrefab.h"
#include "TextureComponent.h"


TestScene::TestScene():
	Scene("TestScene")
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	//auto test = new sf::CircleShape();
	//test->setFillColor(sf::Color::Green);

	CubePrefab* pBackground = new CubePrefab();
	AddChild(pBackground);
	pBackground->SetPosition(0, 0);
	//pBackground->SetSize((float)ServiceLocator::GetWindow()->getSize().x, (float)ServiceLocator::GetWindow()->getSize().y);
	pBackground->SetSize(640,180);
	auto test = new TextureComponent("Resources/Images/background.jpg");
	pBackground->AddComponent(test);

	////pBackground->GetComponent<TextureComponent>()->SetTexture("../Resources/Images/background.jpg");
	//auto test = new TextureComponent();
	//test->GetTexturePos();
}

void TestScene::Update()
{
}

void TestScene::Draw()
{
}
