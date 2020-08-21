#include "OhDeerPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "Observer.h"
#include "Subject.h"

OhDeerEngine::Scene::Scene(const std::string& name) : m_Name(name)
{
	Subject = new OhDeerEngine::Subject();
}

OhDeerEngine::Scene::~Scene()
{
	SafeDelete(Subject);
	//if (Subject != NULL)
	//{
	//	delete Subject;
	//	Subject = nullptr;
	//}
	for (auto pObj : m_Objects)
	{
		SafeDelete(pObj);
	}
}

void OhDeerEngine::Scene::Add(GameObject* object)
{
	const auto& colComp = object->GetComponent<CollisionComponent>();
	if (colComp) m_Collisions.push_back(colComp);
	m_Objects.push_back(object);
}

void OhDeerEngine::Scene::BaseUpdate(float deltaT)
{
	for (auto& object : m_Objects)
	{
		object->Update(deltaT);
	}
	for (auto& object : Subject->Objects)
	{
		object->Update(deltaT);
	}
	for (size_t i = 1; i < m_Collisions.size(); i++)
	{
		for (size_t j = 0; j < m_Collisions.size() - 1; j++)
		{
			m_Collisions[i]->CheckForCollision(m_Collisions[j]);
		}
	}
}

void OhDeerEngine::Scene::FixedUpdate(float deltaT)
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate(deltaT);
	}
	for (auto& object : Subject->Objects)
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
	for (const auto& object : Subject->Objects)
	{
		object->Render();
	}
}
