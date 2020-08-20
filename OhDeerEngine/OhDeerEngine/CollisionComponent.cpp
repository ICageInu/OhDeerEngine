#include "CollisionComponent.h"
#include "OhDeerPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <string>
#include <SDL.h>
#include "Structs.h"
#include "Renderer.h"

OhDeerEngine::CollisionComponent::CollisionComponent(const glm::vec2& pos, float width, float height, bool drawRect) :
	m_DrawRect{ drawRect }
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

void OhDeerEngine::CollisionComponent::CheckForCollision([[maybe_unused]] CollisionComponent* otherCol)
{
	//if (!GetParent()->IsActive) return;
	//if (otherCol->GetParent()->GetChildren().size() != 0)CheckChildrenForCollision(otherCol->GetParent()->GetChildren());

	//if (!otherCol || otherCol == this) return;


	const Rectf otherColl = *otherCol->GetCollision();

	// If one rectangle is on left side of the other or under the other
	if ((m_pCollisionBox->left + m_pCollisionBox->width) < otherColl.left || (otherColl.left + otherColl.width) < m_pCollisionBox->left
		|| m_pCollisionBox->bottom > (otherColl.bottom + otherColl.height) || otherColl.bottom > (m_pCollisionBox->bottom + m_pCollisionBox->height)		)
	{
		return;
	}

	m_pParent->OnTrigger(m_pParent, otherCol->GetParent(), GameObject::TriggerAction::ENTER);

}

//void OhDeerEngine::CollisionComponent::CheckChildrenForCollision(const std::vector<CollisionComponent*>& vColComps)
//{
//	for (size_t i = 0; i < vColComps.size(); i++)
//	{
//			CheckForCollision(vColComps[i]);
//	}
//}

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

void OhDeerEngine::CollisionComponent::Render() const
{
	if (m_DrawRect)
	{
		SDL_Rect rect{};
		rect.x = (int)m_pCollisionBox->left;
		rect.y = (int)m_pCollisionBox->bottom;
		rect.w = (int)m_pCollisionBox->width;
		rect.h = (int)m_pCollisionBox->height;
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 255);
		SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 0, 0, 0);
	}
}

void OhDeerEngine::CollisionComponent::FixedUpdate([[maybe_unused]] const float deltaT) {}
