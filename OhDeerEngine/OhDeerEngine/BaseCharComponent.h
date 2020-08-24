#pragma once
#include "BaseComponent.h"
#include "glm/vec2.hpp"
#include <vector>
#include <SDL.h>

namespace OhDeerEngine
{
	class Command;
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
		BaseCharComponent(GameObject* pParent, RenderComponent* pTexture, CollisionComponent* pCollider,CharType chartype = CharType::Enemy, bool isController = false);
		virtual void Update(const float deltaT) override;
		virtual void Render() const override;
		virtual void FixedUpdate(const float) override;
		int GetScoreToAdd()const;
		int GetCharacterType()const;
		void SetScoreWorth(int score);

		//setters for buttons
		void BindActionA(Command* newCommand);
		void BindActionB(Command* newCommand);
		void BindActionY(Command* newCommand);
		void BindActionX(Command* newCommand);

		void SetKeyboardKeys(const SDL_Keycode& up, const SDL_Keycode& down, const SDL_Keycode& left, const SDL_Keycode& right);
		void SetKeyboardActions(const SDL_Keycode& one, const SDL_Keycode& two, const SDL_Keycode& three, const SDL_Keycode& four);
		bool GetIsConnectedWithController()const;
		void SetIsControlledWithController(bool isControlled);
		glm::vec2 GetDirection()const;
		float GetMovementSpeed()const;
		virtual void ActionOne()=0;
		virtual void ActionTwo() = 0;
		virtual void ActionThree() = 0;
		virtual void ActionFour() = 0;

	protected:
		void Move();
		virtual void SpecificUpdate(const float deltaT) = 0;
	protected:
		Command* m_ButtonA;
		Command* m_ButtonB;
		Command* m_ButtonY;
		Command* m_ButtonX;

		SDL_Keycode m_KeyUp;
		SDL_Keycode m_KeyDown;
		SDL_Keycode m_KeyLeft;
		SDL_Keycode m_KeyRight;
		SDL_Keycode m_KeyActionOne;
		SDL_Keycode m_KeyActionTwo;
		SDL_Keycode m_KeyActionThree;
		SDL_Keycode m_KeyActionFour;


		RenderComponent* m_pTexture;
		CollisionComponent* m_pCollision;
		glm::vec2 m_PosNextFrame;
		glm::vec2 m_Direction;
		float m_MovementSpeed;
		CharType m_CharType;
		int m_ScoreOnDeath;
		bool m_IsController;
	};

}
