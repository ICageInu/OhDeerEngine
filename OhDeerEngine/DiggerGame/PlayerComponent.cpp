#include "OhDeerPCH.h"
#include "Factory.h"
#include "PlayerComponent.h"
#include "Commands.h"
#include "InputManager.h"
#include "glm/geometric.hpp"
#include "TransformComponent.h"
#include "Factory.h"

PlayerComponent::PlayerComponent(OhDeerEngine::GameObject* pParent, OhDeerEngine::RenderComponent* pTexture, OhDeerEngine::CollisionComponent* pCollider, bool isController) :
	BaseCharComponent(pParent, pTexture, pCollider,OhDeerEngine::BaseCharComponent::CharType::Player, isController)
{
	m_PosNextFrame = m_pParent->GetTransform()->GetPosition();
	m_StartPos = m_PosNextFrame;
}

PlayerComponent::~PlayerComponent()
{
	SafeDelete(m_ButtonA);
	SafeDelete(m_ButtonB);
	SafeDelete(m_ButtonX);
	SafeDelete(m_ButtonY);
}


void PlayerComponent::SpecificUpdate([[maybe_unused]] const float deltaT)
{
	if (m_IsController)
	{
		m_Direction = OhDeerEngine::InputManager::GetInstance().GetLeftStick(true);

		if (OhDeerEngine::InputManager::GetInstance().IsPressed(OhDeerEngine::ControllerButton::ButtonA))m_ButtonA->Execute(this);
		else if (OhDeerEngine::InputManager::GetInstance().IsPressed(OhDeerEngine::ControllerButton::ButtonB))m_ButtonB->Execute(this);
		else if (OhDeerEngine::InputManager::GetInstance().IsPressed(OhDeerEngine::ControllerButton::ButtonY))m_ButtonY->Execute(this);
		else if (OhDeerEngine::InputManager::GetInstance().IsPressed(OhDeerEngine::ControllerButton::ButtonX))m_ButtonX->Execute(this);
	}
	else
	{
		if (OhDeerEngine::InputManager::GetInstance().IsDown(m_KeyUp))m_Direction = { 0,-1 };
		else if (OhDeerEngine::InputManager::GetInstance().IsDown(m_KeyDown))m_Direction = { 0,1 };
		else if (OhDeerEngine::InputManager::GetInstance().IsDown(m_KeyLeft))m_Direction = { 1,0 };
		else if (OhDeerEngine::InputManager::GetInstance().IsDown(m_KeyRight))m_Direction = { -1,0 };
		else m_Direction = { 0,0 };

		if (OhDeerEngine::InputManager::GetInstance().IsPressed(m_KeyActionOne))m_ButtonA->Execute(this);
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


void PlayerComponent::SetPlayerId(int id)
{
	m_PlayerId = id;
}

void PlayerComponent::Respawn()
{
	//m_pCollision->->SetPosition(m_StartPos);
	m_PosNextFrame = m_StartPos;
	m_pParent->GetTransform()->SetPosition(m_StartPos);
}

void PlayerComponent::SetController(bool useController)
{
	if (m_IsController)return;
	m_IsController = useController;
}


void PlayerComponent::ActionOne()
{
	std::cout << "there is really only one thing the digger can do: namely spawn the fireballs" << std::endl;
	Factory factory;
	//factory.MakeFireBall(m_pParent->GetTransform()->GetPosition,)
}

void PlayerComponent::ActionTwo() {}

void PlayerComponent::ActionThree() {}

void PlayerComponent::ActionFour() {}
