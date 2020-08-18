#pragma once
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "Commands.h"

class Factory
{
public:
	inline OhDeerEngine::GameObject* MakePlayer(float width,float height)
	{
		OhDeerEngine::GameObject* pPlayer = new OhDeerEngine::GameObject();
		pPlayer->SetTag("player");
		auto pPlayerTexture = new OhDeerEngine::RenderComponent();
		pPlayerTexture->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("digger.png"), (int)width,(int)height);
		//pPlayerTexture->AddRectangleToDraw(150, 150);
		auto pPlayerCol = new OhDeerEngine::CollisionComponent(glm::vec2(0, 0), width,height, true);
		//pPlayerComp->EnableTrigger(true);
		//auto lambdaTrigger = [](GameObject* ob1, GameObject* ob2, GameObject::TriggerAction) 
		//{
		//	std::cout << "actually colliding with: " + ob2->GetTag() << std::endl; 
		//};
		//go->SetOnTriggerCallBack(lambdaTrigger);
		auto pPlayerComp = new PlayerComponent(pPlayer, pPlayerTexture, pPlayerCol);
		pPlayerComp->SetKeyboardKeys(SDLK_w, SDLK_s, SDLK_d, SDLK_a);
		pPlayerComp->BindActionA(new ActionOneCommand());

		return pPlayer;
	}

	inline OhDeerEngine::GameObject* MakeNobbin(float width, float height)
	{
		OhDeerEngine::GameObject* pNobbin = new OhDeerEngine::GameObject();



		return pNobbin;
	}

	inline OhDeerEngine::GameObject* MakeLevel(float width, float height)
	{
		OhDeerEngine::GameObject* pLevel = new OhDeerEngine::GameObject();



		return pLevel;
	}
};