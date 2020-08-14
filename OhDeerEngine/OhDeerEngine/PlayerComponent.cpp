#include "OhDeerPCH.h"
#include "PlayerComponent.h"
#include "Commands.h"
#include "InputManager.h"
#include "glm/geometric.hpp"

OhDeerEngine::PlayerComponent::PlayerComponent(GameObject* pParent, RenderComponent* pTexture, CollisionComponent* pCollider):
	BaseCharComponent(pParent,pTexture,pCollider)
{
	
}

OhDeerEngine::PlayerComponent::~PlayerComponent()
{
	SafeDelete(m_ButtonA);
	SafeDelete(m_ButtonB);
	SafeDelete(m_ButtonX);
	SafeDelete(m_ButtonY);
}


void OhDeerEngine::PlayerComponent::SpecificUpdate([[maybe_unused]]const float deltaT)
{
	m_Direction = InputManager::GetInstance().GetLeftStick(true);
	m_PosNextFrame += m_Direction * deltaT * m_MovementSpeed;
	printf("%f\t%f\n", m_PosNextFrame.x, m_PosNextFrame.y);

	if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonA))m_ButtonA->Execute(this);
	else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonB))m_ButtonB->Execute(this);
	else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonY))m_ButtonY->Execute(this);
	else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonX))m_ButtonX->Execute(this);
}


void OhDeerEngine::PlayerComponent::BindButtonA(Command* newCommand)
{
	m_ButtonA = newCommand;
}

void OhDeerEngine::PlayerComponent::BindButtonB(Command* newCommand)
{
	m_ButtonB = newCommand;
}

void OhDeerEngine::PlayerComponent::BindButtonY(Command* newCommand)
{
	m_ButtonY = newCommand;
}

void OhDeerEngine::PlayerComponent::BindButtonX(Command* newCommand)
{
	m_ButtonX = newCommand;
}

void OhDeerEngine::PlayerComponent::SetPlayerId(int id)
{
	m_PlayerId = id;
}

void OhDeerEngine::PlayerComponent::Jump(){}

void OhDeerEngine::PlayerComponent::ActionOne()
{
	std::cout << "there is really only one thing the digger can do: namely spawn the fireballs" << std::endl;

}

void OhDeerEngine::PlayerComponent::ActionTwo(){}

void OhDeerEngine::PlayerComponent::ActionThree(){}

void OhDeerEngine::PlayerComponent::ActionFour(){}
