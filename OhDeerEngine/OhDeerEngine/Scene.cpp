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

	for (auto pObj : m_Objects)
	{
		SafeDelete(pObj);
	}
}

std::vector<OhDeerEngine::GameObject*> OhDeerEngine::Scene::GetObjects() const
{
	return m_Objects;
}

void OhDeerEngine::Scene::Add(GameObject* object)
{
	const auto& colComp = object->GetComponent<CollisionComponent>();
	if (colComp && !colComp->GetIsStatic()) m_KinematicCollisions.push_back(colComp);
	else if (colComp && colComp->GetIsStatic())m_StaticCollisions.push_back(colComp);
	m_Objects.push_back(object);
}

void OhDeerEngine::Scene::BaseUpdate(float deltaT)
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Update(deltaT);
	}
	for (auto& object : Subject->Objects)
	{
		object->Update(deltaT);
	}
	for (size_t i = 0; i < m_KinematicCollisions.size(); i++)
	{
		if (i != 0)
			m_KinematicCollisions[i]->CheckForCollision(m_KinematicCollisions[i - 1]);
		for (size_t j = 0; j < m_StaticCollisions.size(); j++)
		{
			m_KinematicCollisions[i]->CheckForCollision(m_StaticCollisions[j]);
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
