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

	void SetPlayerId(int id);
	void Respawn();
	void SetController(bool useController);

	virtual void ActionOne() override;
	virtual void ActionTwo() override;
	virtual void ActionThree() override;
	virtual void ActionFour() override;

private:
	glm::vec2 m_StartPos;
	glm::vec2 m_LookDir;
	int m_PlayerId;
};
