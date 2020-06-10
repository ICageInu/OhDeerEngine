#include "pch.h"
#include "TestScene.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"


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

	OhDeer::GameObject* pBackground = new OhDeer::GameObject();
	AddChild(pBackground);
	OhDeer::TransformComponent* pTransform = new OhDeer::TransformComponent();
	pBackground->AddComponent(pTransform);
	pTransform->SetPosition(0, 0);
	//pBackground->SetSize((float)ServiceLocator::GetWindow()->getSize().x, (float)ServiceLocator::GetWindow()->getSize().y);
	pTransform->SetSize(640,180);
	auto test = new OhDeer::TextureComponent("Resources/Images/background.jpg");
	pBackground->AddComponent(test);

	pTransform->GetPosition();
	
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
