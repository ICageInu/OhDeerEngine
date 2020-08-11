#pragma once
#include "BaseComponent.h"
#include "glm/vec2.hpp"
namespace OhDeerEngine
{

	enum CollisionType
	{
		//cheating as this can be seen as a bool
		Kinematic,
		Static
	};

	class CollisionComponent :
		public BaseComponent
	{
	public:
		CollisionComponent(const glm::vec2& pos,float width = 0.0f,float height = 0.0f);
		~CollisionComponent() override;
		//setters
		void SetWidth(float width);
		void SetHeight(float height);
		void SetDimensions(float width,float height);
		void SetDimensions(const glm::vec2& dimensions);
		void EnableTrigger(bool isTrigger);
		void EnableStatic(bool isStatic);
		glm::vec2 GetDimensions()const;
		//getters
		bool IsTrigger()const;
		float GetHeight()const;
		float GetWidth()const;
		void CheckForCollision(GameObject* otherObject);
		void Update(const float deltaT) override;
		void Render() const override;
		void FixedUpdate(const float deltaT)override;
	private:
		glm::vec2 m_Position;
		float m_Width, m_Height;
		CollisionType m_CollisionType;
		bool m_IsTrigger;
	};


}