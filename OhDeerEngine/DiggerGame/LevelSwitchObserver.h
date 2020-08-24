#pragma once
#include "Observer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "EnemyStartComponent.h"
#include "Subject.h"
#include "PickupComponent.h"
class LevelSwitchObserver : public OhDeerEngine::Observer
{
public:
	LevelSwitchObserver() = default;
	virtual ~LevelSwitchObserver() {};
	LevelSwitchObserver(const LevelSwitchObserver& other) = delete;
	LevelSwitchObserver(LevelSwitchObserver&& other) = delete;
	LevelSwitchObserver& operator=(const LevelSwitchObserver& other) = delete;
	LevelSwitchObserver& operator=(LevelSwitchObserver&& other) = delete;
	virtual void OnNotify(const char eventType = 0) override
	{
		if (!m_HasLookedForGems)
		{
			m_HasLookedForGems = true;
			auto obj = OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->GetObjects();
			for (size_t i = 0; i < obj.size(); i++)
			{
				if (obj[i]->GetTag() == "Emerald")
				{
					m_AmountGemsInLevel++;
				}
			}
		}
		if (!m_HasLookedForEnemies)
		{
			m_HasLookedForEnemies = true;
			auto obj = OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->GetObjects();
			for (size_t i = 0; i < obj.size(); i++)
			{
				auto enemComp = obj[i]->GetComponent<EnemyStartComponent>();
				if (enemComp)
				{
					m_AmountEnemiesInLevel = enemComp->GetAmountEnemies();
					break;
				}
			}
		}

		switch (eventType)
		{
		case 'n':
		case 'h':
			m_AmountEnemiesInLevel--;
			break;
		case 'e':
			m_AmountGemsInLevel--;
			break;
		case 'w':
			m_HasLookedForEnemies = false;
			m_HasLookedForGems = false;
			m_AmountGemsInLevel = 0;
			m_AmountEnemiesInLevel = 0;
			bool temp = OhDeerEngine::SceneManager::GetInstance().NextSceneWithSubject();
			OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('i');
			if (!temp)
				OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('L');
			break;
		}
		if (m_AmountGemsInLevel == 0 || m_AmountEnemiesInLevel == 0)
		{
			m_HasLookedForEnemies = false;
			m_HasLookedForGems = false;
			m_AmountGemsInLevel = 0;
			m_AmountEnemiesInLevel = 0;
			//OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('i');
			OhDeerEngine::SceneManager::GetInstance().NextSceneWithSubject();
		}

	};
private:
	int m_AmountGemsInLevel{ 0 }, m_AmountEnemiesInLevel{ 0 };
	bool m_HasLookedForGems{}, m_HasLookedForEnemies{};
};