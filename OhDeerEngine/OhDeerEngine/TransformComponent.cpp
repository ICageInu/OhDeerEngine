#include "TransformComponent.h"

OhDeerEngine::TransformComponent::TransformComponent(const glm::vec2& pos, const float angle):
	m_Position{pos},
	m_Rotation{angle}
{}

void OhDeerEngine::TransformComponent::Update(const float)
{}

void OhDeerEngine::TransformComponent::Render() const
{}

void OhDeerEngine::TransformComponent::FixedUpdate(const float)
{}

void OhDeerEngine::TransformComponent::SetPosition(float x, float y)
{
	SetPosition(glm::vec2(x, y));
}

void OhDeerEngine::TransformComponent::SetPosition(const glm::vec2& position)
{
	m_Position = position;
}

void OhDeerEngine::TransformComponent::SetRotation(float angle)
{
	m_Rotation = angle;
}

const glm::vec2& OhDeerEngine::TransformComponent::GetPosition() const
{
	return m_Position;
}

const float& OhDeerEngine::TransformComponent::GetRotation() const
{

	return m_Rotation;
}
