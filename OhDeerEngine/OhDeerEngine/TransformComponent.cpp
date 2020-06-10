#include "TransformComponent.h"
using namespace OhDeer;


OhDeer::TransformComponent::TransformComponent() {
	Initialize();
}


OhDeer::TransformComponent::~TransformComponent()
{
	SafeDelete(m_pTransform);
}

void OhDeer::TransformComponent::Initialize()
{
	m_IsInitialized = true;
	m_pTransform = new sf::Transform();
}

void OhDeer::TransformComponent::Translate(float x, float y)
{
	Translate(sf::Vector2f(x, y));
}

void OhDeer::TransformComponent::Translate(const sf::Vector2f& dir)
{
	m_pTransform->translate(dir);
}

void OhDeer::TransformComponent::SetPosition(float x, float y)
{
	SetPosition(sf::Vector2(x, y));
}

void OhDeer::TransformComponent::SetPosition(const sf::Vector2<float>& newPos)
{
	m_pTransform->transformPoint(newPos);
}

void OhDeer::TransformComponent::SetSize(float x, float y)
{
	SetSize(sf::Vector2(x, y));
}

void OhDeer::TransformComponent::SetSize(const sf::Vector2<float>& newSize)
{
	m_pTransform->scale(newSize);
}

sf::Vector2f OhDeer::TransformComponent::GetPosition() const
{
	 auto test = m_pTransform->getMatrix();

	 return sf::Vector2f();
}
