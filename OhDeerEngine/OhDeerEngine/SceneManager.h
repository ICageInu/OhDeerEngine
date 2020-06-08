#pragma once
#include "pch.h"
#include "Singleton.h"
class Scene;

class SceneManager :public Singleton<SceneManager>
{
public:
	void CreateScene(Scene* pScene);
	void Initialize();
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void CleanUp();
	Scene* GetActiveScene()const;
private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<Scene*> m_pScenes;
	int m_ActiveScene{};
};

