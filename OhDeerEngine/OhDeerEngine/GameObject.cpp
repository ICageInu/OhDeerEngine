#include "pch.h"
#include "GameObject.h"
#include "TransformComponent.h"

using namespace OhDeer;

GameObject::GameObject():
	m_Width{},
	m_Height{},
	m_HasTexture{false}
{}



void GameObject::AddComponent(BaseComponent* pComp)
{
	//TODO make a failsafe for if a component has already been added
	pComp->SetGameObject(this);
	m_pComponents.push_back(pComp);
}

void GameObject::SetHasTexture(bool hasTexture)
{
	m_HasTexture = hasTexture;
}

void OhDeer::GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}



std::string OhDeer::GameObject::GetTag() const
{
	return m_Tag;
}

TransformComponent* GameObject::GetTransform() const
{
	return GetComponent<TransformComponent>();
}

void OhDeer::GameObject::Initialize()
{
}

void GameObject::Render(sf::RenderWindow* pWindow) const
{
	for (auto comp : m_pComponents)
		comp->Render(pWindow);
}

void OhDeer::GameObject::Update([[maybe_unused]]float deltaT)
{
}

void GameObject::CleanUp() {
	for (BaseComponent* pComp : m_pComponents)
		SafeDelete(pComp);
	m_pComponents.clear();

};
