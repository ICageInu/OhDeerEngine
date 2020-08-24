#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "EnemyComponent.h"
#include "PlayerComponent.h"
class TrackingComponent : public OhDeerEngine::BaseComponent
{
public:
	TrackingComponent(PlayerComponent* pPlayer);
	virtual void Update(const float deltaT) = 0;
	virtual void Render() const = 0;
	virtual void FixedUpdate(const float deltaT) = 0;
};