#include "OhDeerPCH.h"
#include "Scene.h"
#include "GameObject.h"


OhDeerEngine::Scene::Scene(const std::string& name) : m_Name(name)
{}

OhDeerEngine::Scene::~Scene()
{
	for (auto pObj : m_Objects)
	{
		SafeDelete(pObj);
	}
}

void OhDeerEngine::Scene::Add(GameObject* object)
{
	m_Objects.push_back(object);
}

void OhDeerEngine::Scene::BaseUpdate(float deltaT)
{
	for (auto& object : m_Objects)
	{
		object->Update(deltaT);
	}
	for (size_t i = 1; i < m_Objects.size(); i++)
	{
		m_Objects[i]->CheckForCollision(m_Objects[i-1]);
	}
	//Update(deltaT);
}

void OhDeerEngine::Scene::FixedUpdate(float deltaT)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(deltaT);
	}
}

void OhDeerEngine::Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

