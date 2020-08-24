#pragma once
#include "observer.h"
#include "MultiplayerComponent.h"
class TrackerObserver : public OhDeerEngine::Observer
{
public:
	TrackerObserver(MultiplayerComponent* pMultiplayerComp) :m_pMultiplayerComp{ pMultiplayerComp } {};
	//virtual ~HealthObserver() override;
	virtual void OnNotify(const char eventType) override
	{
		switch (eventType)
		{
		case 'u':
			m_pMultiplayerComp->PlayerDied();
			break;
		//case we switching to new level, find new thing
		//case 'i':
		//	m_pMultiplayerComp->PlayerDied();
		//	break;
		}
	};

	TrackerObserver(const TrackerObserver& other) = delete;
	TrackerObserver(TrackerObserver&& other) = delete;
	TrackerObserver& operator=(const TrackerObserver& other) = delete;
	TrackerObserver& operator=(TrackerObserver&& other) = delete;

private:
	MultiplayerComponent* m_pMultiplayerComp;
};