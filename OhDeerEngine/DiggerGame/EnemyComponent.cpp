#include "EnemyComponent.h"
#include "TransformComponent.h"
#include <iostream>


EnemyComponent::EnemyComponent(OhDeerEngine::GameObject* pPlayer, OhDeerEngine::GameObject* pParent, OhDeerEngine::RenderComponent* pTexture, OhDeerEngine::CollisionComponent* pCollider, CharType chartype) :
	BaseCharComponent(pParent, pTexture, pCollider, chartype),
	m_pPlayer{ pPlayer },
	m_AngerIssuesMax{ 8 },
	m_AngerIssues{ m_AngerIssuesMax },
	m_State{ AngerState::Kalm }
{
	m_MovementSpeed *= 1.1f;
	m_PosNextFrame = m_pParent->GetTransform()->GetPosition();
}

void EnemyComponent::SetPlayer(OhDeerEngine::GameObject* pPlayer)
{
	m_pPlayer = { pPlayer };
}

void EnemyComponent::SpecificUpdate(const float deltaT)
{
	//TODO place the logic here for moving towards the player
	glm::vec2 playerPos{};
	if (m_pPlayer)
		playerPos = m_pPlayer->GetTransform()->GetPosition();

	m_Direction = playerPos - m_PosNextFrame;

	if (std::fabsf(m_Direction.x) > std::fabsf(m_Direction.y))
	{
		if (std::signbit(m_Direction.x))
			m_Direction = { -1, 0 };
		else m_Direction = { 1, 0 };
	}
	else
	{
		if (std::signbit(m_Direction.y))
			m_Direction = { 0, -1 };
		else m_Direction = { 0, 1 };
	}

	//printf("%f\t%f\n", m_Direction.x, m_Direction.y);
	m_PosNextFrame += m_Direction * deltaT * m_MovementSpeed;
}
