#pragma once
#include "BaseComponent.h"
#include "glm/vec2.hpp"

namespace OhDeerEngine
{
	class RenderComponent;
	class CollisionComponent;
	class BaseCharComponent :
		public BaseComponent
	{
	public:
		BaseCharComponent(GameObject* pParent, RenderComponent* pTexture, CollisionComponent* pCollider);
		virtual void Update(const float deltaT) override;
		virtual void Render() const override;
		virtual void FixedUpdate(const float) override;
	protected:
		void Move();
		virtual void SpecificUpdate(const float deltaT) = 0;
	protected:
		RenderComponent* m_pTexture;
		CollisionComponent* m_pCollision;
		glm::vec2 m_PosNextFrame;
		glm::vec2 m_Direction;
		float m_MovementSpeed;
	};

}
