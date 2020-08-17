#include "ScoreObserver.h"
#include "BaseCharComponent.h"
#include <iostream>
#include "TextComponent.h"

OhDeerEngine::ScoreObserver::ScoreObserver(TextComponent* pScore):
	m_pScore{pScore}
{
}

void OhDeerEngine::ScoreObserver::OnNotify(const BaseCharComponent& characterComp)
{
	switch (characterComp.GetCharacterType())
	{
	case (characterComp.Enemy):
		m_ScoreValue += characterComp.GetScoreToAdd();
		m_pScore->SetText(std::to_string(m_ScoreValue));
		std::cout << "enemy died" << std::endl;
		break;
	case (characterComp.Player):
		std::cout << "player died" << std::endl;
		break;
	}
}
