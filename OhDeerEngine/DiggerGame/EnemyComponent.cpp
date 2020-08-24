#include "OhDeerPCH.h"
#include "EnemyComponent.h"
#include "TransformComponent.h"
#include <iostream>
#include "CollisionComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include <SDL.h>
#include "InputManager.h"
EnemyComponent::EnemyComponent(OhDeerEngine::GameObject* pPlayer, OhDeerEngine::GameObject* pParent, OhDeerEngine::RenderComponent* pTexture, OhDeerEngine::CollisionComponent* pCollider, CharType chartype) :
	BaseCharComponent(pParent, pTexture, pCollider, chartype),
	m_pPlayer{ pPlayer },
	m_AngerIssuesMax{ 8 },
	m_AngerIssuesDurationMax{ 3 },
	m_AngerIssues{ m_AngerIssuesMax },
	m_AngerIssuesDurationLeft{ m_AngerIssuesDurationMax },
	m_State{ AngerState::Kalm },
	m_SeekerTimerMax{ 3.0f },
	m_SeekerTimer{ -1.0f }
{
	m_MovementSpeed *= 0.5f;
	m_PosNextFrame = m_pParent->GetTransform()->GetPosition();
}

void EnemyComponent::SetPlayer(OhDeerEngine::GameObject* pPlayer)
{
	m_pPlayer = { pPlayer };
}

void EnemyComponent::FixedUpdate([[maybe_unused]] const float deltaT)
{

}

void EnemyComponent::ActionOne()
{

	if (m_State == AngerState::Kalm) m_State = AngerState::Panik;
	else m_State = AngerState::Kalm;
}

void EnemyComponent::SetIsControlled(bool isControlled)
{
	m_IsControlled = isControlled;
}

bool EnemyComponent::GetIsControlled() const
{
	return m_IsControlled;
}


void EnemyComponent::SpecificUpdate(const float deltaT)
{
	if (m_IsControlled)
	{
		PlayerControled(deltaT);
	}
	else
		switch (m_State)
		{
		case AngerState::Kalm:
			AILogicCalm(deltaT);
			if (m_AngerIssues < 0)
			{
				IsAngry = true;
				m_State = AngerState::Panik;
				m_AngerIssues = m_AngerIssuesMax;
			}
			else m_AngerIssues -= deltaT;
			break;
		case AngerState::Panik:
			AILogicAngry(deltaT);
			if (m_AngerIssuesDurationLeft < 0 && !IsColliding)
			{
				IsAngry = false;
				m_State = AngerState::Kalm;
				m_AngerIssuesDurationLeft = m_AngerIssuesDurationMax;
			}
			else m_AngerIssuesDurationLeft -= deltaT;
			break;
		}

}

void EnemyComponent::AILogicCalm(const float deltaT)
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
	tempRect.x = int(m_PosNextFrame.x);
	tempRect.y = int(m_PosNextFrame.y);
	tempRect.w = int(m_pCollision->GetWidth());
	tempRect.h = int(m_pCollision->GetHeight());

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

void EnemyComponent::AILogicAngry(const float deltaT)
{
	switch (m_State)
	{
	case AngerState::Kalm:
		if (m_AngerIssues < 0)
		{
			IsAngry = true;
			m_State = AngerState::Panik;
			m_AngerIssues = m_AngerIssuesMax;
		}
		else m_AngerIssues -= deltaT;
		break;
	case AngerState::Panik:
		if (m_AngerIssuesDurationLeft < 0)
		{
			IsAngry = false;
			m_State = AngerState::Kalm;
			m_AngerIssuesDurationLeft = m_AngerIssuesDurationMax;
		}
		else m_AngerIssuesDurationLeft -= deltaT;
		break;
	}
	glm::vec2 playerPos{};
	if (m_pPlayer)
		playerPos = m_pPlayer->GetTransform()->GetPosition();

	m_Direction = playerPos - m_pParent->GetTransform()->GetPosition();


	if (std::fabsf(m_Direction.x) >= std::fabsf(m_Direction.y))
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
	m_PosNextFrame += m_Direction * deltaT * m_MovementSpeed;
}

void EnemyComponent::PlayerControled(const float deltaT)
{

	if (m_IsController)
	{
		m_Direction = OhDeerEngine::InputManager::GetInstance().GetLeftStick(true);

		if (OhDeerEngine::InputManager::GetInstance().IsPressed(OhDeerEngine::ControllerButton::ButtonA) && m_ButtonA)m_ButtonA->Execute(this);
		else if (OhDeerEngine::InputManager::GetInstance().IsPressed(OhDeerEngine::ControllerButton::ButtonB) && m_ButtonB)m_ButtonB->Execute(this);
		else if (OhDeerEngine::InputManager::GetInstance().IsPressed(OhDeerEngine::ControllerButton::ButtonY) && m_ButtonY)m_ButtonY->Execute(this);
		else if (OhDeerEngine::InputManager::GetInstance().IsPressed(OhDeerEngine::ControllerButton::ButtonX) && m_ButtonX)m_ButtonX->Execute(this);
	}
	else
	{
		if (OhDeerEngine::InputManager::GetInstance().IsDown(m_KeyUp))
		{
			m_Direction = { 0,-1 };
		}
		else if (OhDeerEngine::InputManager::GetInstance().IsDown(m_KeyDown))
		{
			m_Direction = { 0,1 };
		}
		else if (OhDeerEngine::InputManager::GetInstance().IsDown(m_KeyLeft))
		{
			m_Direction = { 1,0 };
		}
		else if (OhDeerEngine::InputManager::GetInstance().IsDown(m_KeyRight))
		{
			m_Direction = { -1,0 };
		}
		else m_Direction = { 0,0 };

		if (OhDeerEngine::InputManager::GetInstance().IsPressed(m_KeyActionOne))
		{
			m_ButtonA->Execute(this);
			//std::cout << "pressed button a " << std::endl;
		}

		else if (OhDeerEngine::InputManager::GetInstance().IsPressed(m_KeyActionTwo))m_ButtonB->Execute(this);
		else if (OhDeerEngine::InputManager::GetInstance().IsPressed(m_KeyActionThree))m_ButtonY->Execute(this);
		else if (OhDeerEngine::InputManager::GetInstance().IsPressed(m_KeyActionFour))m_ButtonX->Execute(this);
	}
	m_PosNextFrame += m_Direction * deltaT * m_MovementSpeed;
	if (m_PosNextFrame.x < 0 ||
		m_PosNextFrame.x + m_pCollision->GetWidth() > OhDeerEngine::ServiceLocator::GetGameHandlers()->windowDimensions.x ||
		m_PosNextFrame.y  < m_pCollision->GetHeight() ||
		m_PosNextFrame.y + m_pCollision->GetHeight()  > OhDeerEngine::ServiceLocator::GetGameHandlers()->windowDimensions.y)
	{
		m_PosNextFrame -= m_Direction * deltaT * m_MovementSpeed;
	}
}
