#pragma once
#include <BaseComponent.h>
#include "glm/vec2.hpp"
class PickupComponent :
    public OhDeerEngine::BaseComponent
{
public:
	virtual void Update(const float deltaT) override;
	virtual void Render() const override {};
	virtual void FixedUpdate(const float deltaT) override {};
	bool IsFalling{ false }, IsPickup{ false };

private:
	const glm::vec2 m_FallingDir{ 0,1 };
	glm::vec2 m_FallingPos;
	float m_MovingSpeed{ 19.62f };
};

