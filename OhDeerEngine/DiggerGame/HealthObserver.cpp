#include "HealthObserver.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Subject.h"

HealthObserver::HealthObserver(const std::array<OhDeerEngine::RenderComponent*, 5>& rendercomps) :
	OhDeerEngine::Observer(),
	m_Lives{ rendercomps },
	m_AmountHealth{ 3 }
{

}


//there will be a couple different eventTypes,just to make it so that we can differentiate between what's picked up
//use first letter of the event
void HealthObserver::OnNotify(const char eventType)
{

	switch (eventType)
	{
	case '+':
		if (m_AmountHealth < (int)m_Lives.size())
		{
			m_AmountHealth++;
			m_Lives[m_AmountHealth-1]->GetParent()->IsActive = true;
		}
		break;
	case '-':
		if (m_AmountHealth > 1)
		{
			OhDeerEngine::SceneManager::GetInstance().ReloadScene();
			m_Lives[m_AmountHealth-1]->GetParent()->IsActive = false;
			m_AmountHealth--;
		}
		else OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('L');
		break;
	}


}
