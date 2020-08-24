#include "InputComponent.h"
#include "InputManager.h"
#include "SceneManager.h"
#include <iostream>
#include "Scene.h"
#include "PlayerComponent.h"
#include "Subject.h"

InputComponent::InputComponent(OhDeerEngine::TextComponent* pText) :
	m_pText{ pText }

{
	OhDeerEngine::InputManager::GetInstance().CleanInputString();
}
void InputComponent::Update([[maybe_unused]] const float deltaT)
{
	if (!m_pParent->IsActive) return;
	m_Initials = OhDeerEngine::InputManager::GetInstance().GetInputString();
	if (m_Initials.size() == 0)m_Initials = "...";
	m_pText->SetText(m_Initials);
	if (!m_SetControllerInput && OhDeerEngine::InputManager::GetInstance().AnyButtonPressed())
	{
		//only at start can button on controller be pressed and player be controlled with controller
		m_SetControllerInput = true;
		for (auto pScene : OhDeerEngine::SceneManager::GetInstance().GetScenes())
		{
			for (size_t i = 0; i < pScene->GetObjects().size(); i++)
			{
				auto playerCol = pScene->GetObjects()[i]->GetComponent<PlayerComponent>();
				if (playerCol)
				{
					playerCol->SetController(true);
					break;
				}
			}
		}
	}


	if (OhDeerEngine::InputManager::GetInstance().IsPressed(SDLK_SPACE) || m_SetControllerInput && OhDeerEngine::InputManager::GetInstance().IsPressed(OhDeerEngine::ControllerButton::ButtonA))
	{
		//make it so that the saved name is also passed on so it can be linked with the score
		m_pParent->SetEnabledDisabled(false);
		OhDeerEngine::InputManager::GetInstance().CleanInputString();
		//TODO this might make program crash
		//find a way to save the initials without making the program crash
		//OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->Objects.push_back(m_pParent);
		m_pParent->IsActive = false;
		OhDeerEngine::SceneManager::GetInstance().NextScene();
	}

}

std::string InputComponent::GetInitials() const
{
	return m_Initials;
}
