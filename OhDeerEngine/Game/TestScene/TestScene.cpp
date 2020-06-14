#include "pch.h"
#include "TestScene.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextComponent.h"


TestScene::TestScene() :
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

	m_pBackground = new OhDeer::GameObject();
	AddChild(m_pBackground);
	OhDeer::TransformComponent* pTransform = new OhDeer::TransformComponent();
	m_pBackground->AddComponent(pTransform, true);
	pTransform->Translate(0, 0);
	//pBackground->SetSize((float)ServiceLocator::GetWindow()->getSize().x, (float)ServiceLocator::GetWindow()->getSize().y);
	pTransform->SetScale(1.5, 1.5);
	//pTransform->SetSize(640, 180);
	auto test = new OhDeer::TextureComponent("Resources/Images/background.jpg");
	m_pBackground->AddComponent(test);
	pTransform->GetPosition();
	pTransform->Translate(150, -400);

	m_Fps = new OhDeer::GameObject();
	OhDeer::TextComponent* pText = new OhDeer::TextComponent();
	m_Fps->AddComponent(pText);
	OhDeer::TransformComponent* pTransform2 = new OhDeer::TransformComponent();
	m_Fps->AddComponent(pTransform2);
	pText->SetFont("./Resources/Font/Lingua.otf");
	pText->SetText("this be text");
	AddChild(m_Fps);
	pTransform2->Translate(20, 40);







	////pBackground->GetComponent<TextureComponent>()->SetTexture("../Resources/Images/background.jpg");
	//auto test = new TextureComponent();
	//test->GetTexturePos();
}

void TestScene::Update(float deltaT)
{
	m_FrameCounter++;
	m_FpsInterval += deltaT;

	if (m_FpsInterval >= 1.f)
	{
		//std::cout << "FPS: " << m_FrameCounter << std::endl;
 		m_Fps->GetComponent<OhDeer::TextComponent>()->SetText("FPS: " + std::to_string(m_FrameCounter));
		m_FpsInterval -= 1.f;
		m_FrameCounter = 0;
	}
	//sf::Vector2f newpos = m_pBackground->GetTransform()->GetPosition();
	//m_pBackground->GetTransform()->Translate(0.001f+newpos.x, 0.001f-newpos.y);
	//assert(m_pBackground->GetComponent<OhDeer::TransformComponent>()->GetPosition() == sf::Vector2f(15, 4));
}

void TestScene::Draw([[maybe_unused]] sf::RenderWindow* pWindow)const
{

	//assert(pTransform->GetPosition() == sf::Vector2f(15, 4));
}
