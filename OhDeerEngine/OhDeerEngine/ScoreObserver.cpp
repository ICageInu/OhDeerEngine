#include "ScoreObserver.h"
#include "BaseCharComponent.h"
#include <iostream>
#include "TextComponent.h"
#include "SceneManager.h"
#include "Scene.h"

OhDeerEngine::ScoreObserver::ScoreObserver(TextComponent* pScore):
	m_pScore{ pScore },
	m_ScoreGained{0},
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
		m_ScoreGained += 250;
		break;
	case 'h':
		m_Update = true;
		m_ScoreGained += 250;
		break;
	case 'e':
		m_Update = true;
		m_ScoreGained += 25;
		break;
	case 'g':
		m_Update = true;
		m_ScoreGained += 500;
		break;

	case 'l':
		OhDeerEngine::SceneManager::GetInstance().NextScene();
		break;

	}
	
	if (m_Update) 
	{
		m_ScoreValue += m_ScoreGained;

		if (m_ScoreGained > 2000)
		{
			m_ScoreGained = 0;
			OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('+');
		}
		m_Update = false;
		m_pScore->SetText(std::to_string(m_ScoreValue));
	}
}
