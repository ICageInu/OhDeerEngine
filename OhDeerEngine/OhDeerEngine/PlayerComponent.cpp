#include "OhDeerPCH.h"
#include "PlayerComponent.h"
#include "Commands.h"
#include "InputManager.h"
#include "glm/geometric.hpp"
#include "TransformComponent.h"

PlayerComponent::PlayerComponent(OhDeerEngine::GameObject* pParent, OhDeerEngine::RenderComponent* pTexture, OhDeerEngine::CollisionComponent* pCollider, bool isController) :
	BaseCharComponent(pParent, pTexture, pCollider),
	m_KeyUp{},
	m_KeyDown{},
	m_KeyLeft{},
	m_KeyRight{},
	m_KeyActionOne{},
	m_KeyActionTwo{},
	m_KeyActionThree{},
	m_KeyActionFour{},
	m_ButtonA{ nullptr },
	m_ButtonB{ nullptr },
	m_ButtonY{ nullptr },
	m_ButtonX{ nullptr },
	m_IsController{ isController }
{
	m_PosNextFrame = m_pParent->GetTransform()->GetPosition();
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


void PlayerComponent::BindActionA(Command* newCommand)
{
	m_ButtonA = newCommand;
}

void PlayerComponent::BindActionB(Command* newCommand)
{
	m_ButtonB = newCommand;
}

void PlayerComponent::BindActionY(Command* newCommand)
{
	m_ButtonY = newCommand;
}

void PlayerComponent::BindActionX(Command* newCommand)
{
	m_ButtonX = newCommand;
}

void PlayerComponent::SetPlayerId(int id)
{
	m_PlayerId = id;
}

void PlayerComponent::Respawn()
{
	m_pParent->GetTransform()->SetPosition(m_StartPos);
}

void PlayerComponent::SetKeyboardKeys(const SDL_Keycode& up, const SDL_Keycode& down, const SDL_Keycode& left, const SDL_Keycode& right)
{
	m_KeyUp = up;
	m_KeyDown = down;
	m_KeyLeft = left;
	m_KeyRight = right;
}

void PlayerComponent::Jump() {}

void PlayerComponent::ActionOne()
{
	std::cout << "there is really only one thing the digger can do: namely spawn the fireballs" << std::endl;

}

void PlayerComponent::ActionTwo() {}

void PlayerComponent::ActionThree() {}

void PlayerComponent::ActionFour() {}
