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
	CubePrefab* pBackground = new CubePrefab();
	AddChild(pBackground);
	pBackground->SetPosition(0, 0);
	pBackground->SetSize((float)ServiceLocator::GetWindow()->getSize().x, (float)ServiceLocator::GetWindow()->getSize().y);
	pBackground->AddComponent(new TextureComponent("../Resources/Images/background.jpg"));

	////pBackground->GetComponent<TextureComponent>()->SetTexture("../Resources/Images/background.jpg");
	auto test = new TextureComponent();
	test->GetTexturePos();
}

void TestScene::Update()
{
}

void TestScene::Draw()
{
}
