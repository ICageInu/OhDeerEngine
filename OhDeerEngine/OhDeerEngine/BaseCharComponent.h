#pragma once
#include "BaseComponent.h"
#include "glm/vec2.hpp"
#include <vector>

namespace OhDeerEngine
{
	class RenderComponent;
	class CollisionComponent;
	class BaseCharComponent :
		public BaseComponent
	{
	public:
		enum CharType 
		{
			Player,
			Enemy
		};
	public:
		BaseCharComponent(GameObject* pParent, RenderComponent* pTexture, CollisionComponent* pCollider,CharType chartype = CharType::Enemy);
		virtual void Update(const float deltaT) override;
		virtual void Render() const override;
		virtual void FixedUpdate(const float) override;
		int GetScoreToAdd()const;
		int GetCharacterType()const;
		void SetScoreWorth(int score);

	protected:
		void Move();
		virtual void SpecificUpdate(const float deltaT) = 0;
	protected:

		RenderComponent* m_pTexture;
		CollisionComponent* m_pCollision;
		glm::vec2 m_PosNextFrame;
		glm::vec2 m_Direction;
		float m_MovementSpeed;
		CharType m_CharType;
		int m_ScoreOnDeath;
	};

}
