#include "SceneManager.h"
#include "SceneManager.h"
#include "SceneManager.h"
#include "OhDeerPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "Subject.h"
#include "Observer.h"

void OhDeerEngine::SceneManager::Update(float deltaT)
{
	m_Scenes[m_ActiveScene]->BaseUpdate(deltaT);
	//DEBUG BUTTONS
	//if (InputManager::GetInstance().IsPressed(SDLK_p)) PreviousScene();

	if (InputManager::GetInstance().IsPressed(SDLK_n))
	{
		NextSceneWithSubject();
	}
}

void OhDeerEngine::SceneManager::FixedUpdate(float deltaT)
{
	//for (auto& scene : m_Scenes)
	//{
	//	if (!scene->m_IsActive) continue;
	//	scene->FixedUpdate(deltaT);
	//}
	m_Scenes[m_ActiveScene]->FixedUpdate(deltaT);
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

std::vector<OhDeerEngine::Scene*> OhDeerEngine::SceneManager::GetScenes() const
{
	return m_Scenes;
}

OhDeerEngine::Scene* OhDeerEngine::SceneManager::GetActiveScene() const
{
	return m_Scenes[m_ActiveScene];
}

void OhDeerEngine::SceneManager::NextScene()
{
	if (m_ActiveScene + 1 != m_Scenes.size())
	{
		m_ActiveScene++;
	}
}

void OhDeerEngine::SceneManager::NextScene(OhDeerEngine::Subject* pSubject)
{

	if (m_ActiveScene + 1 != m_Scenes.size())
	{
		m_ActiveScene++;
		m_Scenes[m_ActiveScene]->Subject->operator=(*pSubject);
	}
}

void OhDeerEngine::SceneManager::NextSceneWithSubject()
{
	if (m_ActiveScene + 1 != m_Scenes.size())
	{
		m_ActiveScene++;
		m_Scenes[m_ActiveScene]->Subject->operator=(*m_Scenes[m_ActiveScene - 1]->Subject);
	}
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

OhDeerEngine::Scene* OhDeerEngine::SceneManager::GetScene(const std::string& name)const
{
	for (size_t i = 0; i < m_Scenes.size(); i++)
	{
		if (m_Scenes[i]->m_Name == name) return m_Scenes[i];
	}
	return nullptr;
}

OhDeerEngine::Scene* OhDeerEngine::SceneManager::GetScene(size_t index) const
{
	if (index > 0 || index < m_Scenes.size())
		return m_Scenes[index];

	return nullptr;
}

OhDeerEngine::SceneManager::~SceneManager()
{
	//SafeDelete(m_Scenes[m_ActiveScene]->Subject);

	for (auto pScene : m_Scenes)
	{
		SafeDelete(pScene);
	}
	m_Scenes.clear();
}
