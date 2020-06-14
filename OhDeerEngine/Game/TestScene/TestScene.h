#pragma once
#include "Scene.h"
class TestScene :
	public OhDeer::Scene
{
public:
	TestScene();
	virtual ~TestScene();
	TestScene(const TestScene& other) = delete;
	TestScene(TestScene&& other) = delete;
	TestScene& operator=(const TestScene& other) = delete;
	TestScene& operator=(TestScene&& other) = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw(sf::RenderWindow* pWindow)const override;

private:
	OhDeer::GameObject* m_pBackground;
	OhDeer::GameObject* m_Fps;
};

