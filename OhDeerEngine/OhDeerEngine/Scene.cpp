#include "OhDeerPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "Observer.h"

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




//subject
OhDeerEngine::Subject::~Subject()
{
	for (auto pObs :Observers)
	{
		SafeDelete(pObs);
	}
	for (auto pObj :Objects)
	{
		SafeDelete(pObj);
	}
}

void OhDeerEngine::Subject::RegisterObserver(Observer* pObserver)
{
	for (Observer* pComp : Observers)
	{

		if (typeid(*pComp) == typeid(*pObserver))
		{
			throw std::exception("RegisterObserver: This observer already exists");
		}
	}
	Observers.push_back(pObserver);
}

bool OhDeerEngine::Subject::UnRegisterObserver(Observer* pObserver)
{
	auto it = std::find_if(Observers.cbegin(), Observers.cend(), [pObserver](Observer* pObs)
		{
			return typeid(*pObs) == typeid(*pObserver);
		});
	if (it != Observers.cend())
	{
		Observers.erase(it);
		return true;
	}
	return false;
}

void OhDeerEngine::Subject::NotifyAllObservers(const uint8_t event)
{
	for (Observer* pObs : Observers)
	{
		pObs->OnNotify(event);
	}
}
