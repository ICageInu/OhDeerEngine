
#include "BaseComponent.h"
#include "GameObject.h"
using namespace OhDeer;
BaseComponent::BaseComponent():
	m_IsInitialized(false)
{
}

void OhDeer::BaseComponent::SetGameObject(GameObject* parent)
{
	m_pParent = parent;
}
