#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"
namespace OhDeerEngine
{

	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(const glm::vec2& pos = { 0.f,0.f }, const float angle = 0.f);

		void Update(const float deltaT)override;
		void Render() const override;
		void FixedUpdate(const float deltaT) override;

		//setters
		void SetPosition(float x, float y);
		void SetPosition(const glm::vec2& position);
		void SetRotation(float angle);
	
		//getters
		const glm::vec2& GetPosition() const;
		const float& GetRotation() const;

	private:
		glm::vec2 m_Position;
		float m_Rotation;
	};

}
