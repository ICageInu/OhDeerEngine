#pragma once
#include <BaseComponent.h>
#include "PlayerComponent.h"
class MultiplayerComponent :
    public OhDeerEngine::BaseComponent
{
public:
	MultiplayerComponent();
	virtual void Update(const float deltaT) override;
	virtual void Render() const override {};
	virtual void FixedUpdate([[maybe_unused]] const float deltaT) override {};
	void PlayerDied();
private:
	PlayerComponent* m_pPlayer;
	bool m_FoundPlayer;
	bool m_IsControllingEnemy;
};

