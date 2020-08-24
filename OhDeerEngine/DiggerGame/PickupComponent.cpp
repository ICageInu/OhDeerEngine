#include "OhDeerPCH.h"
#include "PickupComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
PickupComponent::PickupComponent(PlayerComponent* pPlayer, const glm::vec2& startPos) :
	m_pPlayer{pPlayer},
	m_StartPos{ startPos },
	m_FallingDir{ 0,1},
	m_MovingSpeed{75.0f}
{
}
void PickupComponent::Update(const float deltaT)
{
	if (IsPickup) return;
	if (IsBeingTouched)
	{
		if (!m_pParent->GetComponent<OhDeerEngine::CollisionComponent>()->IsOverlapping(
			m_pPlayer->GetParent()->GetComponent<OhDeerEngine::CollisionComponent>()->GetCollision()))
		{
			HasBeenTouched = true;
			IsBeingTouched = false;
			//IsFalling = true;
		}
	}
	if (!IsBeingTouched && HasBeenTouched)
	{
		auto parPos = m_pParent->GetTransform()->GetPosition();
		m_pParent->GetTransform()->SetPosition(parPos + m_FallingDir * deltaT * m_MovingSpeed);

		auto parHeight = m_pParent->GetComponent<OhDeerEngine::CollisionComponent>()->GetHeight();
		if (parPos.y > m_StartPos.y + parHeight * 4.0f)IsFalling = true;
		if (IsFalling = true && parPos.y + parHeight > OhDeerEngine::ServiceLocator::GetGameHandlers()->windowDimensions.y)
		{
			IsPickup = true;
			IsFalling = false;
		}
	}
}
