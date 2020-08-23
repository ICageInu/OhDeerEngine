#include "CollisionComponent.h"
#include "OhDeerPCH.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <string>
#include <SDL.h>
#include "Structs.h"
#include "Renderer.h"


OhDeerEngine::CollisionComponent::CollisionComponent(const glm::vec2& pos, float width, float height,const glm::vec2& offset, bool drawRect) :
	m_DrawRect{ drawRect },
	m_Offset{offset}
{
	m_pCollisionBox = new SDL_Rect();
	m_pCollisionBox->x = (int)pos.x;
	m_pCollisionBox->y = (int)pos.y;
	m_pCollisionBox->w = (int)width;
	m_pCollisionBox->h = (int)height;

}

OhDeerEngine::CollisionComponent::~CollisionComponent()
{
	SafeDelete(m_pCollisionBox);
}

void OhDeerEngine::CollisionComponent::SetWidth(float width)
{
	m_pCollisionBox->w = (int)width;
}

void OhDeerEngine::CollisionComponent::SetHeight(float height)
{
	m_pCollisionBox->h = (int)height;
}

void OhDeerEngine::CollisionComponent::SetDimensions(float width, float height)
{
	SetDimensions(glm::vec2(width, height));
}

void OhDeerEngine::CollisionComponent::SetDimensions(const glm::vec2& dimensions)
{
	m_pCollisionBox->w = (int)dimensions.x;
	m_pCollisionBox->h = (int)dimensions.y;
}

void OhDeerEngine::CollisionComponent::EnableStatic(bool isStatic)
{
	m_CollisionType = CollisionType(isStatic);
}

bool OhDeerEngine::CollisionComponent::GetIsStatic() const
{
	return m_CollisionType;
}

glm::vec2 OhDeerEngine::CollisionComponent::GetDimensions() const
{
	return glm::vec2(m_pCollisionBox->w, m_pCollisionBox->h);
}

SDL_Rect* OhDeerEngine::CollisionComponent::GetCollision() const
{

	return m_pCollisionBox;
}

bool OhDeerEngine::CollisionComponent::IsTrigger() const
{
	return m_IsTrigger;
}

float OhDeerEngine::CollisionComponent::GetHeight() const
{
	return float(m_pCollisionBox->h);
}

float OhDeerEngine::CollisionComponent::GetWidth() const
{
	return float(m_pCollisionBox->w);
}

void OhDeerEngine::CollisionComponent::CheckForCollision([[maybe_unused]] CollisionComponent* otherCol)
{

	if (m_CollisionType) return;


	// If one rectangle is on left side of the other or under the other

	if (IsOverlapping(otherCol))
		m_pParent->OnTrigger(m_pParent, otherCol->GetParent(), GameObject::TriggerAction::ENTER);

}

bool OhDeerEngine::CollisionComponent::IsOverlapping(CollisionComponent* otherObject)
{

	const SDL_Rect otherColl = *otherObject->GetCollision();
	if ((m_pCollisionBox->x + m_pCollisionBox->w) < otherColl.x || (otherColl.x + otherColl.w) < m_pCollisionBox->x
		|| m_pCollisionBox->y > (otherColl.y + otherColl.h) || otherColl.y > (m_pCollisionBox->y + m_pCollisionBox->h))
	{
		return false;
	}
	return true;
}

bool OhDeerEngine::CollisionComponent::IsOverlapping(SDL_Rect* otherObj)
{
	if ((m_pCollisionBox->x + m_pCollisionBox->w) <= otherObj->x || (otherObj->x + otherObj->w) <= m_pCollisionBox->x
		|| m_pCollisionBox->y >= (otherObj->y + otherObj->h) || otherObj->y >= (m_pCollisionBox->y + m_pCollisionBox->h))
	{
		return false;
	}
	return true;
}

bool OhDeerEngine::CollisionComponent::IsOverlapping(SDL_Rect* Obj1, SDL_Rect* Obj2)
{
	if ((Obj1->x + Obj1->w) <= Obj2->x || (Obj2->x + Obj2->w) <= Obj1->x
		|| Obj1->y >= (Obj2->y + Obj2->h) || Obj2->y >= (Obj1->y + Obj1->h))
	{
		return false;
	}
	return true;
}

bool OhDeerEngine::CollisionComponent::IsPointInRect(const glm::vec2& point, const SDL_Rect& otherObject)
{
	if (m_CollisionType) return false;

	return (point.x >= otherObject.x && point.x <= otherObject.x + otherObject.w &&
		point.y >= otherObject.y && point.y <= otherObject.y + otherObject.h);
}
//something seems to be going wrong
bool OhDeerEngine::CollisionComponent::IsPointInRect(const glm::vec2& point, SDL_Rect* pOtherObject)
{
	if (m_CollisionType) return false;

	return (point.x >= pOtherObject->x && point.x <= pOtherObject->x + pOtherObject->w &&
		point.y >= pOtherObject->y && point.y <= pOtherObject->y + pOtherObject->h);
}

//this one is for checking under the box
//very specific case
bool OhDeerEngine::CollisionComponent::IsPointInRect(CollisionComponent* otherCol)
{
	if (m_CollisionType) return false;

	const SDL_Rect otherColl = *otherCol->GetCollision();

	if (m_pCollisionBox->x + m_pCollisionBox->w / 2.f >= otherColl.x &&
		m_pCollisionBox->x + m_pCollisionBox->w / 2.f <= otherColl.x + otherColl.w &&
		m_pCollisionBox->y + m_pCollisionBox->h / 2.f >= otherColl.y &&
		m_pCollisionBox->y + m_pCollisionBox->h / 2.f <= otherColl.y + otherColl.h)
		return true;
	return false;
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
		m_pCollisionBox->x = int(temp.x + m_Offset.x);
		m_pCollisionBox->y = int(temp.y+ m_Offset.y);
	}
	if (m_CollisionType && glm::vec2(m_pCollisionBox->x + m_Offset.x, m_pCollisionBox->y + m_Offset.y) != m_pParent->GetTransform()->GetPosition())
	{
		throw std::runtime_error(std::string("Trying to move a static Collider"));
	}


}

void OhDeerEngine::CollisionComponent::Render() const
{
	if (m_DrawRect)
	{
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 255);
		SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), m_pCollisionBox);
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 0, 0, 0);
	}
}

void OhDeerEngine::CollisionComponent::FixedUpdate([[maybe_unused]] const float deltaT) {}
