#include "OhDeerPCH.h"
#include "EnemyComponent.h"
#include "TransformComponent.h"
#include <iostream>
#include "CollisionComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include <SDL.h>

EnemyComponent::EnemyComponent(OhDeerEngine::GameObject* pPlayer, OhDeerEngine::GameObject* pParent, OhDeerEngine::RenderComponent* pTexture, OhDeerEngine::CollisionComponent* pCollider, CharType chartype) :
	BaseCharComponent(pParent, pTexture, pCollider, chartype),
	m_pPlayer{ pPlayer },
	m_AngerIssuesMax{ 8 },
	m_AngerIssues{ m_AngerIssuesMax },
	m_State{ AngerState::Kalm },
	m_SeekerTimerMax{ 3.0f },
	m_SeekerTimer{ -1.0f }
{
	m_MovementSpeed *= 1.25f;
	m_PosNextFrame = m_pParent->GetTransform()->GetPosition();
}

void EnemyComponent::SetPlayer(OhDeerEngine::GameObject* pPlayer)
{
	m_pPlayer = { pPlayer };
}

void EnemyComponent::FixedUpdate([[maybe_unused]] const float deltaT)
{

}

void EnemyComponent::SpecificUpdate(const float deltaT)
{

	//TODO place the logic here for moving towards the player
	glm::vec2 playerPos{};
	if (m_pPlayer)
		playerPos = m_pPlayer->GetTransform()->GetPosition();

	m_Direction = playerPos - m_pParent->GetTransform()->GetPosition();


	glm::vec2 vertDir, horzDir, ogPos = m_PosNextFrame;
	bool fastestVert{}, fastestHorz{};

	if (std::fabsf(m_Direction.x) >= std::fabsf(m_Direction.y))
	{
		fastestHorz = true;
	}
	else
	{
		fastestVert = true;
	}

	if (std::signbit(m_Direction.x))
		horzDir = { -1, 0 };
	else horzDir = { 1, 0 };
	if (std::signbit(m_Direction.y))
		vertDir = { 0, -1 };
	else vertDir = { 0, 1 };

	auto tempPosVert = m_PosNextFrame + vertDir * deltaT * m_MovementSpeed;
	auto tempPosHorz = m_PosNextFrame + horzDir * deltaT * m_MovementSpeed;

	////this is most likely going to fuckup in some cases, as this doesn't make the characters move in another direction
	////this wil keep them stuck in their spot
	////I just realised that this makes it so that it's only checking for objects  
	auto pColVector = OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->GetStaticCollisions();
	bool goingHorz{}, goingVert{};
	if (fastestHorz)
	{
		goingHorz = true;
		m_PosNextFrame = tempPosHorz;
	}
	else
	{
		goingVert = true;
		m_PosNextFrame = tempPosVert;
	}
	bool intersect{};

	SDL_Rect tempRect{};
	tempRect.x = m_PosNextFrame.x;
	tempRect.y = m_PosNextFrame.y;
	tempRect.w = m_pCollision->GetWidth();
	tempRect.h = m_pCollision->GetHeight();

	for (size_t i = 0; i < pColVector.size(); i++)
	{
		if (!pColVector[i]->GetParent()->IsActive)continue;
		auto temp = pColVector[i]->GetCollision();
		intersect = m_pCollision->IsOverlapping(&tempRect, temp);
		if (intersect)
		{
			if (goingHorz)
				m_PosNextFrame = tempPosVert;
			else 
				m_PosNextFrame = tempPosHorz;
		}
	}

	//std::cout << "horz: " + std::to_string(doNotMoveHorz) + "\t" + "vert: " + std::to_string(doNotMoveVert) << std::endl;

	//printf("%f\t%f\n", m_Direction.x, m_Direction.y);

}