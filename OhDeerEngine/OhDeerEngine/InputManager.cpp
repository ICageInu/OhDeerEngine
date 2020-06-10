#include "InputManager.h"

using namespace OhDeer;

OhDeer::InputManager::~InputManager()
{
}

bool InputManager::AddInputAction(Command action)
{
	//const auto it = std::find(m_InputActions.cbegin(), m_InputActions.cend(), action);
	//if (it != m_InputActions.cend())
	//{
	//	return false;
	//}
	//m_InputActions[action.ActionID] = action;
	return true;
}

bool InputManager::IsActionTriggered(int actionID)
{
	//this is wrong
	//TODO FIX
	return m_InputActions[actionID].buttonState == ButtonState::RELEASED;
}

sf::Vector2<int> InputManager::GetMousePosition()
{
	return sf::Mouse::getPosition();
}
