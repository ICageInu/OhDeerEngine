#include "InputComponent.h"
#include "InputManager.h"
#include "SceneManager.h"
#include <iostream>
InputComponent::InputComponent(OhDeerEngine::TextComponent* pText) :
	m_pText{ pText }
{

}
void InputComponent::Update([[maybe_unused]] const float deltaT)
{
	m_Initials = OhDeerEngine::InputManager::GetInstance().GetInputString();
	if (m_Initials.size() == 0)m_Initials = "...";
	m_pText->SetText(m_Initials);
	if (!m_SetControllerInput && OhDeerEngine::InputManager::GetInstance().AnyButtonPressed())
	{
		m_SetControllerInput = true;
	}


	if (OhDeerEngine::InputManager::GetInstance().IsPressed(SDLK_SPACE))
	{
		//make it so that the saved name is also passed on so it can be linked with the score
		OhDeerEngine::SceneManager::GetInstance().NextScene();
	}

}
