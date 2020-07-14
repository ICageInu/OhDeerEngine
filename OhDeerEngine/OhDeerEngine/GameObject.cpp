#include "OhDeerPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

OhDeerEngine::GameObject::GameObject(const glm::vec2& pos, const float angle)
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
	for (BaseComponent* pComp : m_Components)
	{
		pComp->Update(deltaT);
	}
}
void OhDeerEngine::GameObject::FixedUpdate(float deltaT)
{
	for (BaseComponent* pComp : m_Components)
	{
		pComp->FixedUpdate(deltaT);
	}
}
void OhDeerEngine::GameObject::Render() const
{
	for (BaseComponent* pComp : m_Components)
	{
		pComp->Render();
	}

}

//void OhDeerEngine::GameObject::SetTexture(const std::string& filename)
//{
//	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
//}