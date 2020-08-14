#pragma once
#include "BaseCharComponent.h"

namespace OhDeerEngine
{
	class Command;
	class PlayerComponent :
		public BaseCharComponent
	{
	public:
		PlayerComponent(GameObject* pParent, RenderComponent* pTexture, CollisionComponent* pCollider);
		virtual ~PlayerComponent()override;
		virtual void SpecificUpdate(const float deltaT) override;

		//setters for buttons
		void BindButtonA(Command* newCommand);
		void BindButtonB(Command* newCommand);
		void BindButtonY(Command* newCommand);
		void BindButtonX(Command* newCommand);

		void SetPlayerId(int id);

		//actions able to be done through commands
		void Jump();
		void ActionOne();
		void ActionTwo();
		void ActionThree();
		void ActionFour();
	private:
		Command* m_ButtonA;
		Command* m_ButtonB;
		Command* m_ButtonY;
		Command* m_ButtonX;
		int m_PlayerId;
	};
}