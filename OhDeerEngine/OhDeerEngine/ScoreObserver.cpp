#include "ScoreObserver.h"
#include "BaseCharComponent.h"
#include <iostream>
#include "TextComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Subject.h"

OhDeerEngine::ScoreObserver::ScoreObserver(TextComponent* pScore) :
	Observer(),
	m_pScore{ pScore },
	m_ScoreValue{0},
	m_Update{false}
{
}

//n for nobbins,h for hobbins, e for emeralds, g, for gold, l for level
void OhDeerEngine::ScoreObserver::OnNotify(const char eventType)
{
	switch (eventType)
	{
	case 'n':
		m_Update = true;
		m_ScoreValue += 250;
		break;
	case 'h':
		m_Update = true;
		m_ScoreValue += 250;
		break;
	case 'e':
		m_Update = true;
		m_ScoreValue += 25;
		break;
	case 'g':
		m_Update = true;
		m_ScoreValue += 500;
		break;

	case 'l':
		OhDeerEngine::SceneManager::GetInstance().NextSceneWithSubject();
		break;

	}

	if (m_Update) 
	{
		m_Update = false;

		if (m_ScoreValue % 20000 == 0)
		{
			OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('+');
		}
		m_pScore->SetText(std::to_string(m_ScoreValue));
	}
}
