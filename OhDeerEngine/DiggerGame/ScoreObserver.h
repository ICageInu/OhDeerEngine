#pragma once
#include "Observer.h"
#include "TextComponent.h"
#include "BaseCharComponent.h"

class ScoreObserver :
	public OhDeerEngine::Observer
{
public:
	ScoreObserver(OhDeerEngine::TextComponent* pScore);
	virtual void OnNotify(const char eventType = 0) override;
	ScoreObserver(const ScoreObserver& other) = delete;
	ScoreObserver(ScoreObserver&& other) = delete;
	ScoreObserver& operator=(const ScoreObserver& other) = delete;
	ScoreObserver& operator=(ScoreObserver&& other) = delete;
private:
	//needs a reference to the score gameobject with a textcomponent telling the player how much score they have
	OhDeerEngine::TextComponent* m_pScore;
	int m_ScoreValue;
	bool m_Update;
};

