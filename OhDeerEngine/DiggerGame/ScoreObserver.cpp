#include "ScoreObserver.h"
#include "BaseCharComponent.h"
#include <iostream>
#include "TextComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Subject.h"

ScoreObserver::ScoreObserver(OhDeerEngine::TextComponent* pScore) :
	Observer(),
	m_pScore{ pScore },
	m_EmeraldTimingMax{10.0f},
	m_ScoreValue{0},
	m_EmeraldsInSuccession{0},
	m_Update{false}
{
}

//n for nobbins,h for hobbins, e for emeralds, g, for gold, l for level
void ScoreObserver::OnNotify(const char eventType)
{
	switch (eventType)
	{
	case 'n':
		m_Update = true;
		m_ScoreValueForLife =m_ScoreValue += 250;
		break;
	case 'h':
		m_Update = true;
		m_ScoreValueForLife = m_ScoreValue += 250;
		break;
	case 'E':
		m_Update = true;
		m_ScoreValueForLife = m_ScoreValue += 250;
		break;
	case 'e':
		m_EmeraldsInSuccession++;
		m_Update = true;
		m_ScoreValueForLife = m_ScoreValue += 25;
		//std::cout << "picked up emerald" << std::endl;
		break;
	case 'g':
		m_Update = true;
		m_ScoreValueForLife = m_ScoreValue += 500;
		break;
	case 't':
		m_EmeraldTiming++;
		break;

	}


	if (m_EmeraldsInSuccession == 8 && m_EmeraldTiming < m_EmeraldTimingMax)
	{
		//std::cout << "+250" << std::endl;
		m_EmeraldsInSuccession = 0;
		OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('E');
		m_Update = true;
	}
	if (m_EmeraldTiming > m_EmeraldTimingMax) m_EmeraldTiming = 0;

	if (m_Update) 
	{
		m_Update = false;

		if (m_ScoreValueForLife - 20000 > 0)
		{
			m_ScoreValueForLife -= 20000;
			OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('+');
		}
		m_pScore->SetText(std::to_string(m_ScoreValue));
	}
}


int ScoreObserver::GetScore() const
{
	return m_ScoreValue;
}
