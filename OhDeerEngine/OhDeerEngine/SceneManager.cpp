#include "OhDeerPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"

void OhDeerEngine::SceneManager::Update(float deltaT)
{
	//for(auto& scene : m_Scenes)
	//{
	//	if (!scene->m_IsActive) continue;
	//	scene->BaseUpdate(deltaT);
	//}





	m_Scenes[m_ActiveScene]->BaseUpdate(deltaT);
}

void OhDeerEngine::SceneManager::FixedUpdate(float deltaT)
{
	//for (auto& scene : m_Scenes)
	//{
	//	if (!scene->m_IsActive) continue;
	//	scene->FixedUpdate(deltaT);
	//}
	m_Scenes[m_ActiveScene]->FixedUpdate(deltaT);
	//DEBUG BUTTONS
	if (InputManager::GetInstance().IsPressed(SDLK_p)) PreviousScene();
	if (InputManager::GetInstance().IsPressed(SDLK_n)) NextScene();
}

void OhDeerEngine::SceneManager::Render()
{
	//for (const auto& scene : m_Scenes)
	//{
	//	if (!scene->m_IsActive) continue;
	//	scene->Render();
	//}
	m_Scenes[m_ActiveScene]->Render();
}

void OhDeerEngine::SceneManager::NextScene()
{
	if (m_ActiveScene + 1 != m_Scenes.size()) m_ActiveScene++;
}

void OhDeerEngine::SceneManager::PreviousScene()
{
	if (m_ActiveScene - 1 != 0) m_ActiveScene--;
}

OhDeerEngine::Scene* OhDeerEngine::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	//scene->m_IsActive = false;
	m_Scenes.push_back(scene);
	return scene;
}

void OhDeerEngine::SceneManager::AddGameScene(OhDeerEngine::Scene* pScene)
{
	const auto it = std::find(m_Scenes.begin(), m_Scenes.end(), pScene);

	if (it == m_Scenes.end())
	{
		m_Scenes.push_back(pScene);
		//pScene->Initialize();
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
