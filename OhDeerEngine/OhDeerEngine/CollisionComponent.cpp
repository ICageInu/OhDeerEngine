#include "OhDeerPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <string>
#include <SDL.h>
#include "Structs.h"

OhDeerEngine::CollisionComponent::CollisionComponent(const glm::vec2& pos, float width, float height)
{
	m_pCollisionBox = new Rectf();
	m_pCollisionBox->left = pos.x;
	m_pCollisionBox->bottom = pos.y;
	m_pCollisionBox->width = width;
	m_pCollisionBox->height = height;
	
}

OhDeerEngine::CollisionComponent::~CollisionComponent()
{
	SafeDelete(m_pCollisionBox);
}

void OhDeerEngine::CollisionComponent::SetWidth(float width)
{
	m_pCollisionBox->width = width;
}

void OhDeerEngine::CollisionComponent::SetHeight(float height)
{
	m_pCollisionBox->height = height;
}

void OhDeerEngine::CollisionComponent::SetDimensions(float width, float height)
{
	SetDimensions(glm::vec2(width, height));
}

void OhDeerEngine::CollisionComponent::SetDimensions(const glm::vec2& dimensions)
{
	m_pCollisionBox->width = dimensions.x;
	m_pCollisionBox->height = dimensions.y;
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
	return glm::vec2(m_pCollisionBox->width, m_pCollisionBox->height);
}

Rectf* OhDeerEngine::CollisionComponent::GetCollision() const
{
	return m_pCollisionBox;
}

bool OhDeerEngine::CollisionComponent::IsTrigger() const
{
	return m_IsTrigger;
}

float OhDeerEngine::CollisionComponent::GetHeight() const
{
	return m_pCollisionBox->height;
}

float OhDeerEngine::CollisionComponent::GetWidth() const
{
	return m_pCollisionBox->width;
}

void OhDeerEngine::CollisionComponent::CheckForCollision([[maybe_unused]] GameObject* otherObject)
{
	const auto collComp = otherObject->GetComponent<CollisionComponent>();
	if (!collComp) return;
	const auto otherColl = collComp->GetCollision();
	// If one rectangle is on left side of the other
	if ((m_pCollisionBox->left + m_pCollisionBox->width) < otherColl->left || (otherColl->left + otherColl->width) < m_pCollisionBox->left)
	{
		return;
	}

	// If one rectangle is under the other
	if (m_pCollisionBox->bottom > (otherColl->bottom + otherColl->height) || otherColl->bottom > (m_pCollisionBox->bottom + m_pCollisionBox->height))
	{
		return;
	}

	m_pParent->OnTrigger(m_pParent, otherObject, GameObject::TriggerAction::ENTER);

}

void OhDeerEngine::CollisionComponent::Update([[maybe_unused]] const float deltaT)
{
	if (!m_CollisionType)
	{
		glm::vec2 temp = m_pParent->GetTransform()->GetPosition();
		m_pCollisionBox->left = temp.x;
		m_pCollisionBox->bottom = temp.y;
	}
	if (m_CollisionType && glm::vec2(m_pCollisionBox->left, m_pCollisionBox->bottom) != m_pParent->GetTransform()->GetPosition())
	{
		throw std::runtime_error(std::string("Trying to move a static Collider"));
	}

}

void OhDeerEngine::CollisionComponent::Render() const{}

void OhDeerEngine::CollisionComponent::FixedUpdate([[maybe_unused]] const float deltaT){}
