#include "OhDeerPCH.h"
#include "PlayerComponent.h"
#include "Commands.h"
#include "InputManager.h"
#include "glm/geometric.hpp"
#include "GameObject.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"

OhDeerEngine::PlayerComponent::PlayerComponent(GameObject* pParent, RenderComponent* pTexture, CollisionComponent* pCollider, bool isController) :
	BaseCharComponent(pParent, pTexture, pCollider),
	m_KeyUp{},
	m_KeyDown{},
	m_KeyLeft{},
	m_KeyRight{},
	m_KeyActionOne{},
	m_KeyActionTwo{},
	m_KeyActionThree{},
	m_KeyActionFour{},
	m_ButtonA{nullptr},
	m_ButtonB{nullptr},
	m_ButtonY{nullptr},
	m_ButtonX{nullptr},
	m_IsController{ isController }
{

}

OhDeerEngine::PlayerComponent::~PlayerComponent()
{
	SafeDelete(m_ButtonA);
	SafeDelete(m_ButtonB);
	SafeDelete(m_ButtonX);
	SafeDelete(m_ButtonY);
}


void OhDeerEngine::PlayerComponent::SpecificUpdate([[maybe_unused]] const float deltaT)
{
	if (m_IsController)
	{
		m_Direction = InputManager::GetInstance().GetLeftStick(true);

		if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonA))m_ButtonA->Execute(this);
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonB))m_ButtonB->Execute(this);
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonY))m_ButtonY->Execute(this);
		else if (InputManager::GetInstance().IsPressed(ControllerButton::ButtonX))m_ButtonX->Execute(this);
	}
	else
	{
		if (InputManager::GetInstance().IsDown(m_KeyUp))m_Direction = { 0,1 };
		else if (InputManager::GetInstance().IsDown(m_KeyDown))m_Direction = { 0,-1 };
		else if (InputManager::GetInstance().IsDown(m_KeyLeft))m_Direction = { 1,0 };
		else if (InputManager::GetInstance().IsDown(m_KeyRight))m_Direction = { -1,0 };
		else m_Direction = { 0,0 };

		if (InputManager::GetInstance().IsPressed(m_KeyActionOne))m_ButtonA->Execute(this);
		else if (InputManager::GetInstance().IsPressed(m_KeyActionTwo))m_ButtonB->Execute(this);
		else if (InputManager::GetInstance().IsPressed(m_KeyActionThree))m_ButtonY->Execute(this);
		else if (InputManager::GetInstance().IsPressed(m_KeyActionFour))m_ButtonX->Execute(this);
	}


	m_PosNextFrame += m_Direction * deltaT * m_MovementSpeed;
}


void OhDeerEngine::PlayerComponent::BindActionA(Command* newCommand)
{
	m_ButtonA = newCommand;
}

void OhDeerEngine::PlayerComponent::BindActionB(Command* newCommand)
{
	m_ButtonB = newCommand;
}

void OhDeerEngine::PlayerComponent::BindActionY(Command* newCommand)
{
	m_ButtonY = newCommand;
}

void OhDeerEngine::PlayerComponent::BindActionX(Command* newCommand)
{
	m_ButtonX = newCommand;
}

void OhDeerEngine::PlayerComponent::SetPlayerId(int id)
{
	m_PlayerId = id;
}

void OhDeerEngine::PlayerComponent::SetKeyboardKeys(const SDL_Keycode& up, const SDL_Keycode& down, const SDL_Keycode& left, const SDL_Keycode& right)
{
	m_KeyUp = up;
	m_KeyDown = down;
	m_KeyLeft = left;
	m_KeyRight = right;
}

void OhDeerEngine::PlayerComponent::Jump() {}

void OhDeerEngine::PlayerComponent::ActionOne()
{
	std::cout << "there is really only one thing the digger can do: namely spawn the fireballs" << std::endl;

}

void OhDeerEngine::PlayerComponent::ActionTwo() {}

void OhDeerEngine::PlayerComponent::ActionThree() {}

void OhDeerEngine::PlayerComponent::ActionFour() {}
