#pragma once
#include "BaseCharComponent.h"
#include <SDL.h>

#include "GameObject.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"

class Command;

class PlayerComponent :
	public OhDeerEngine::BaseCharComponent
{
public:
	PlayerComponent(OhDeerEngine::GameObject* pParent,
		OhDeerEngine::RenderComponent* pTexture, OhDeerEngine::CollisionComponent* pCollider, bool isController = false);
	virtual ~PlayerComponent()override;
	virtual void SpecificUpdate(const float deltaT) override;

	//setters for buttons
	void BindActionA(Command* newCommand);
	void BindActionB(Command* newCommand);
	void BindActionY(Command* newCommand);
	void BindActionX(Command* newCommand);

	void SetPlayerId(int id);
	void Respawn();

	void SetKeyboardKeys(const SDL_Keycode& up, const SDL_Keycode& down, const SDL_Keycode& left, const SDL_Keycode& right);

	//actions able to be done through commands
	void Jump();
	void ActionOne();
	void ActionTwo();
	void ActionThree();
	void ActionFour();
private:
	SDL_Keycode m_KeyUp;
	SDL_Keycode m_KeyDown;
	SDL_Keycode m_KeyLeft;
	SDL_Keycode m_KeyRight;
	SDL_Keycode m_KeyActionOne;
	SDL_Keycode m_KeyActionTwo;
	SDL_Keycode m_KeyActionThree;
	SDL_Keycode m_KeyActionFour;
	Command* m_ButtonA;
	Command* m_ButtonB;
	Command* m_ButtonY;
	Command* m_ButtonX;
	glm::vec2 m_StartPos;
	int m_PlayerId;
	bool m_IsController;
};
