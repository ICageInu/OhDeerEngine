#include "OhDeerPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void OhDeerEngine::SceneManager::Update(float deltaT)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaT);
	}
}

void OhDeerEngine::SceneManager::FixedUpdate(float deltaT)
{
	for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(deltaT);
	}
}

void OhDeerEngine::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

OhDeerEngine::Scene& OhDeerEngine::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_Scenes.push_back(scene);
	return *scene;
}

OhDeerEngine::SceneManager::~SceneManager()
{
	for (auto pScene : m_Scenes) 
	{
		SafeDelete(pScene);
	}
}
