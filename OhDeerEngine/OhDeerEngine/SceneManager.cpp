#include "SceneManager.h"
#include "Scene.h"

using namespace OhDeer;

void SceneManager::Update(float deltaTime)
{
	for (auto& scene : m_pScenes)
	{
		scene->BaseUpdate(deltaTime);
	}
}

void SceneManager::Render(sf::RenderWindow* pWindow)
{

	for (const auto& scene : m_pScenes)
	{
		scene->BaseRender(pWindow);
	}

}

void SceneManager::CleanUp()
{
	for (Scene* pScene : m_pScenes)
		SafeDelete(pScene);
	m_pScenes.clear();
}

Scene* SceneManager::GetActiveScene() const
{
	return m_pScenes[m_ActiveScene];
}

void SceneManager::CreateScene(Scene* pScene)
{

	const auto it = std::find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it == m_pScenes.end())
	{
		m_pScenes.push_back(pScene);
	}

	//const auto scene = new Scene(name);
	//m_pScenes.push_back(scene);
	//return  *scene;
}

void SceneManager::Initialize()
{
	//auto shape = new sf::CircleShape(100.f);
	//shape->setFillColor(sf::Color::Green);
	for (const auto& scene : m_pScenes)
	{
		scene->BaseInitialize();
	}
}
