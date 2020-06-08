#include "pch.h"
#include "GameObject.h"


void GameObject::AddComponent(BaseComponent* pComp)
{
	//TODO make a failsafe for if a component has already been added
	m_pComponents.push_back(pComp);
}

void GameObject::SetHasTexture(bool hasTexture)
{
	m_HasTexture = hasTexture;
}

sf::Transform* GameObject::GetTransform() const
{
	return nullptr;
}

void GameObject::Render(sf::RenderWindow* pWindow) const
{
	for (auto comp : m_pComponents)
		comp->Render(pWindow);
}

void GameObject::CleanUp() {
	for (BaseComponent* pComp : m_pComponents)
		SafeDelete(pComp);
	m_pComponents.clear();
	SafeDelete(m_pTransform);
	CleanUpSpecific();
};
