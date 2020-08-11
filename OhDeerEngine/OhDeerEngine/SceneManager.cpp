#include "OhDeerPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void OhDeerEngine::SceneManager::Update(float deltaT)
{
	for(auto& scene : m_Scenes)
	{
		scene->BaseUpdate(deltaT);
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

//OhDeerEngine::Scene& OhDeerEngine::SceneManager::CreateScene(const std::string& name)
//{
//	const auto scene = new Scene(name);
//	m_Scenes.push_back(scene);
//	return *scene;
//}

void OhDeerEngine::SceneManager::AddGameScene(OhDeerEngine::Scene* pScene)
{
	const auto it = std::find(m_Scenes.begin(), m_Scenes.end(), pScene);

	if (it == m_Scenes.end())
	{
		m_Scenes.push_back(pScene);
		pScene->Initialize();
	}
}

OhDeerEngine::SceneManager::~SceneManager()
{
	for (auto pScene : m_Scenes) 
	{
		SafeDelete(pScene);
	}
	m_Scenes.clear();
}
