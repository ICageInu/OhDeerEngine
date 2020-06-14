#include "Scene.h"
#include "Scene.h"
#include "GameObject.h"
#include "pch.h"
#include "TextureComponent.h"

using namespace OhDeer;
//unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() {
	for (GameObject* pObj : m_pObjects) {
		pObj->CleanUp();
		SafeDelete(pObj);
	}
	m_pObjects.clear();
}

void Scene::AddChild(GameObject* pObject)
{
	m_pObjects.push_back(pObject);
}

void Scene::BaseInitialize()
{
	Initialize();
}

void Scene::BaseUpdate(float deltaTime)
{
	for (auto& object : m_pObjects)
	{
		object->Update(deltaTime);
	}
	Update(deltaTime);
}

void Scene::BaseRender(sf::RenderWindow* pWindow) const
{
	for (const GameObject* object : m_pObjects)
	{
		object->Render(pWindow);
	}
	Draw(pWindow);
}

