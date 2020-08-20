#include "GameObject.h"
#include "OhDeerPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"

OhDeerEngine::GameObject::GameObject(const glm::vec2& pos, const float angle):
	IsActive{ true }
{
	AddComponent(new TransformComponent(pos, angle));
}

OhDeerEngine::GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_Components)
	{
		SafeDelete(pComp);
	}
	m_Components.clear();
}




void OhDeerEngine::GameObject::AddComponent(BaseComponent* pComponent)
{
	for (BaseComponent* pComp : m_Components)
	{

		if (typeid(*pComp) == typeid(*pComponent))
		{
			throw std::exception("AddComponent: This component already exists");
		}
	}
	m_Components.push_back(pComponent);
	pComponent->SetParent(this);
}

void OhDeerEngine::GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

void OhDeerEngine::GameObject::Update(float deltaT)
{
	if (!IsActive) return;

	for (BaseComponent* pComp : m_Components)
	{
		pComp->Update(deltaT);
	}
}
void OhDeerEngine::GameObject::FixedUpdate(float deltaT)
{
	if (!IsActive) return;

	for (BaseComponent* pComp : m_Components)
	{
		pComp->FixedUpdate(deltaT);
	}
}
void OhDeerEngine::GameObject::Render() const
{
	if (!IsActive) return;

	for (BaseComponent* pComp : m_Components)
	{
		pComp->Render();
	}

}
OhDeerEngine::TransformComponent* OhDeerEngine::GameObject::GetTransform()const
{
	const auto temp = GetComponent<TransformComponent>();
	if (temp) return temp;
	else
		throw std::runtime_error(std::string("trying to get a transform on an object that doesn't have one") + m_Tag);

}

//void OhDeerEngine::GameObject::CheckForCollision(GameObject* pOther)
//{
//	if (!m_IsActive) return;
//	const auto colComp = GetComponent<CollisionComponent>();
//	if (colComp)
//	{
//		colComp->CheckForCollision(pOther);
//	}
//}

void OhDeerEngine::GameObject::SetOnTriggerCallBack(TriggerCallback triggerCallback)
{
	m_OnTriggerCallback = triggerCallback;
}

void OhDeerEngine::GameObject::OnTrigger(GameObject* triggerObject, GameObject* otherObject, TriggerAction action)
{
	if (m_OnTriggerCallback)
		m_OnTriggerCallback(triggerObject, otherObject, action);
}

std::string OhDeerEngine::GameObject::GetTag() const
{
	return m_Tag;
}

void OhDeerEngine::GameObject::SetEnabledDisabled(bool isEnabled)
{
	IsActive = isEnabled;
}

//bool OhDeerEngine::GameObject::GetIsActive() const
//{
//	return m_IsActive;
//}
