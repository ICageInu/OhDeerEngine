#pragma once
#include "BaseComponent.h"
#include "glm/vec2.hpp"
#include <SDL_rect.h>


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
		CollisionComponent() = default;
		CollisionComponent(const glm::vec2& pos, float width = 0.0f, float height = 0.0f, const glm::vec2& offset = {0,0}, bool drawRect = false);
		~CollisionComponent() override;
		//setters
		void SetWidth(float width);
		void SetHeight(float height);
		void SetDimensions(float width,float height);
		void SetDimensions(const glm::vec2& dimensions);
		void EnableStatic(bool isStatic);
		bool GetIsStatic()const;
		glm::vec2 GetDimensions()const;
		SDL_Rect* GetCollision()const;
		//getters
		bool IsTrigger()const;
		float GetHeight()const;
		float GetWidth()const;
		void CheckForCollision(CollisionComponent* otherObject);
		bool IsOverlapping(CollisionComponent* otherObject);
		bool IsOverlapping(SDL_Rect* otherObj);
		bool IsOverlapping(SDL_Rect* Obj1,SDL_Rect* Obj2);
		bool IsPointInRect(const glm::vec2& point,const SDL_Rect& otherObject);
		bool IsPointInRect(const glm::vec2& point, SDL_Rect* pOtherObject);
		bool IsPointInRect(CollisionComponent* otherObject);
		//void CheckChildrenForCollision(const std::vector<CollisionComponent*>& otherObject);
		void Update(const float deltaT) override;
		void Render() const override;
		void FixedUpdate(const float deltaT)override;
	private:
		glm::vec2 m_Offset;
		SDL_Rect* m_pCollisionBox;
		CollisionType m_CollisionType;
		bool m_IsTrigger;
		bool m_DrawRect;
	};


}