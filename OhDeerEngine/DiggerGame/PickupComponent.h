#pragma once
#include <BaseComponent.h>
#include "glm/vec2.hpp"
class PlayerComponent;
class PickupComponent :
    public OhDeerEngine::BaseComponent
{
public:
	PickupComponent(PlayerComponent* pPlayer,const glm::vec2& startPos);
	virtual void Update(const float deltaT) override;
	virtual void Render() const override {};
	virtual void FixedUpdate(const float deltaT) override {};
	bool IsFalling{ false }, IsPickup{ false }, IsBeingTouched{ false }, HasBeenTouched{ false };

private:
	PlayerComponent* m_pPlayer;
	const glm::vec2 m_StartPos;
	const glm::vec2 m_FallingDir;
	glm::vec2 m_FallingPos;
	float m_MovingSpeed;
};

