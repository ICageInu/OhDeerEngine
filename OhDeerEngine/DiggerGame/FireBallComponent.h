#pragma once
#include "BaseComponent.h"
#include "glm/vec2.hpp"
#include "GameObject.h"
#include "TransformComponent.h"
class FireBallComponent : public OhDeerEngine::BaseComponent
{
public:
	FireBallComponent(const glm::vec2& dir) : m_Direction{ dir }, m_MovementSpeed{ 75.0f }{}



	virtual void Update(const float deltaT) override
	{
		auto pos = m_pParent->GetTransform()->GetPosition();
		m_pParent->GetTransform()->SetPosition(pos + m_Direction * deltaT * m_MovementSpeed);
	};
	virtual void Render() const override {};
	virtual void FixedUpdate([[maybe_unused]] const float deltaT) override {	};
private:
	const glm::vec2 m_Direction;
	const float m_MovementSpeed;
};