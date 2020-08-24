#include "OhDeerPCH.h"
#include "PickupComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "Scene.h"
#include "SceneManager.h"
PickupComponent::PickupComponent(PlayerComponent* pPlayer, const glm::vec2& startPos) :
	m_pPlayer{ pPlayer },
	m_StartPos{ startPos },
	m_FallingDir{ 0,1 },
	m_FallSpeed{ 75.0f },
	m_TouchedTimerMax{ 0.1f },
	m_TouchedTimer{ m_TouchedTimerMax },
	m_MovingSpeed{}
{
}
void PickupComponent::Update(const float deltaT)
{
	//we move for previous frame
	auto parPos = m_pParent->GetTransform()->GetPosition();
	m_pParent->GetTransform()->SetPosition(parPos + m_Direction * deltaT * m_MovingSpeed);
	if (parPos.x < 0 || parPos.y < 0 ||
		parPos.x + m_pParent->GetComponent<OhDeerEngine::CollisionComponent>()->GetWidth() > OhDeerEngine::ServiceLocator::GetGameHandlers()->windowDimensions.x)
	{

		IsFalling = true;
	}

	if (parPos.y + m_pParent->GetComponent<OhDeerEngine::CollisionComponent>()->GetHeight() >
		OhDeerEngine::ServiceLocator::GetGameHandlers()->windowDimensions.y)
		IsPickup = true;

	if (IsPickup)
	{
		IsFalling = false;
		m_Direction = { 0,0 };
	}

	if (!IsPickup && IsBeingTouched && !m_pParent->GetComponent<OhDeerEngine::CollisionComponent>()->IsOverlapping(
		m_pPlayer->GetParent()->GetComponent<OhDeerEngine::CollisionComponent>()->GetCollision()))
	{
		m_TouchedTimer -= deltaT;
		if (m_TouchedTimer < 0)
		{
			IsFalling = false;
			m_Direction = { 0,0 };
			HasBeenTouched = true;
			IsBeingTouched = false;
		}
		return;
	}
	else
		m_TouchedTimer = m_TouchedTimerMax;

	if (!IsBeingTouched && IsColliding())m_Direction = { 0,0 };

	float height = m_pParent->GetComponent<OhDeerEngine::CollisionComponent>()->GetHeight();
	if (HasBeenTouched && !IsPickup && IsFalling && !m_DidSetStartPos)
	{
		//set startPos
		m_DidSetStartPos = true;
		m_StartPos = parPos;
		m_Direction = m_FallingDir;
	}

	else if (IsFalling && parPos.y  > m_StartPos.y + height / 1.5f && IsColliding())
	{
		IsPickup = true;
	}

	//making it so that if comes into contact with sand it stops
	if (!IsPickup && !IsFalling && !IsBeingTouched && !IsColliding())
	{
		IsFalling = true;
	}

}

void PickupComponent::SetDirection(const glm::vec2& dir)
{
	m_Direction = dir;
}
void PickupComponent::SetSpeed(const float speed)
{
	m_MovingSpeed = speed;
}

bool PickupComponent::IsColliding()const
{
	auto objs = OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->GetStaticCollisions();
	bool isTouchingSand{ false };
	auto colComp = m_pParent->GetComponent<OhDeerEngine::CollisionComponent>();
	for (size_t i = 0; i < objs.size(); i++)
	{
		if (!objs[i]->GetParent()->IsActive || objs[i]->GetParent()->GetTag() != "Level")continue;
		if (colComp->IsOverlapping(objs[i]))
		{
			isTouchingSand = true;
			break;
		}
	}

	return isTouchingSand;
}
