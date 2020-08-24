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
	void SetDirection(const glm::vec2& dir);
	void SetSpeed(const float speed);
	
private:
	PlayerComponent* m_pPlayer;
	glm::vec2 m_StartPos;
	const glm::vec2 m_FallingDir;
	glm::vec2 m_Direction;
	glm::vec2 m_FallingPos;
	const float m_FallSpeed;
	const float m_TouchedTimerMax;
	float m_TouchedTimer;
	float m_MovingSpeed;
	bool m_DidSetStartPos;
	bool IsColliding()const;
};

