#include "OhDeerPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <string>
#include <SDL.h>

OhDeerEngine::CollisionComponent::CollisionComponent(const glm::vec2& pos, float width, float height):
	m_Position{pos},
	m_Width{width},
	m_Height{height}
{}

OhDeerEngine::CollisionComponent::~CollisionComponent()
{
}

void OhDeerEngine::CollisionComponent::SetWidth(float width)
{
	m_Width = width;
}

void OhDeerEngine::CollisionComponent::SetHeight(float height)
{
	m_Height = height;
}

void OhDeerEngine::CollisionComponent::SetDimensions(float width, float height)
{
	SetDimensions(glm::vec2(width, height));
}

void OhDeerEngine::CollisionComponent::SetDimensions(const glm::vec2& dimensions)
{
	m_Width = dimensions.x;
	m_Height = dimensions.y;
}

void OhDeerEngine::CollisionComponent::EnableTrigger(bool isTrigger)
{
	m_IsTrigger = isTrigger;
}

void OhDeerEngine::CollisionComponent::EnableStatic(bool isStatic)
{
	m_CollisionType = CollisionType(isStatic);
}

glm::vec2 OhDeerEngine::CollisionComponent::GetDimensions() const
{
	// TODO: insert return statement here
	return glm::vec2(m_Width, m_Height);
}

bool OhDeerEngine::CollisionComponent::IsTrigger() const
{
	return m_IsTrigger;
}

float OhDeerEngine::CollisionComponent::GetHeight() const
{
	return m_Height;
}

float OhDeerEngine::CollisionComponent::GetWidth() const
{
	return m_Width;
}

void OhDeerEngine::CollisionComponent::CheckForCollision([[maybe_unused]]GameObject* otherObject)
{
	glm::vec2 leftTopCorner, rightTopCorner, rightBottomCorner, leftBottomCorner;
	leftBottomCorner = m_Position;

}

void OhDeerEngine::CollisionComponent::Update([[maybe_unused]]const float deltaT)
{
	if (!m_CollisionType) 
	{
		m_Position = m_pParent->GetTransform()->GetPosition();
	}
	if (m_CollisionType && m_Position != m_pParent->GetTransform()->GetPosition()) 
	{
		throw std::runtime_error(std::string("Trying to move a static Collider"));
	}

}

void OhDeerEngine::CollisionComponent::Render() const
{

}

void OhDeerEngine::CollisionComponent::FixedUpdate([[maybe_unused]] const float deltaT)
{
}
