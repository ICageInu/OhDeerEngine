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
	inline OhDeerEngine::GameObject* MakePlayer(const glm::vec2& pos,float width,float height)
	{
		OhDeerEngine::GameObject* pPlayer = new OhDeerEngine::GameObject();
		pPlayer->SetTag("player");
		auto pPlayerTexture = new OhDeerEngine::RenderComponent();
		pPlayerTexture->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("digger.png"), (int)width,(int)height);
		//pPlayerTexture->AddRectangleToDraw(150, 150);
		auto pPlayerCol = new OhDeerEngine::CollisionComponent(pos, width,height, true);
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

	inline OhDeerEngine::GameObject* MakeNobbin(const glm::vec2& pos, float width, float height)
	{
		OhDeerEngine::GameObject* pNobbin = new OhDeerEngine::GameObject();



		return pNobbin;
	}

	inline OhDeerEngine::GameObject* MakeLevel(const glm::vec2& pos, float width, float height)
	{
		OhDeerEngine::GameObject* pLevel = new OhDeerEngine::GameObject(pos);
		pLevel->SetTag("Level");
		auto pCol = new OhDeerEngine::CollisionComponent(pos,width,height,true);
		pCol->EnableStatic(true);
		auto pTex = new OhDeerEngine::RenderComponent();
		pTex->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("wall.png"), (int)width, (int)height);


		pLevel->AddComponent(pCol);
		pLevel->AddComponent(pTex);
		return pLevel;
	}

	inline OhDeerEngine::GameObject* MakeEmerald(const glm::vec2& pos, float width, float height)
	{
		OhDeerEngine::GameObject* pLevel = new OhDeerEngine::GameObject(pos);
		pLevel->SetTag("Tunnel");
		auto pCol = new OhDeerEngine::CollisionComponent(pos,width,height,true);
		pCol->EnableStatic(true);
		auto pTex = new OhDeerEngine::RenderComponent();
		pTex->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("emerald.png"), (int)width, (int)height);


		pLevel->AddComponent(pCol);
		pLevel->AddComponent(pTex);
		return pLevel;
	}

	inline OhDeerEngine::GameObject* MakeMoneyBag(const glm::vec2& pos, float width, float height)
	{
		OhDeerEngine::GameObject* pLevel = new OhDeerEngine::GameObject(pos);
		pLevel->SetTag("Tunnel");
		auto pCol = new OhDeerEngine::CollisionComponent(pos,width,height,true);
		pCol->EnableStatic(true);
		auto pTex = new OhDeerEngine::RenderComponent();
		pTex->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("Gold.png"), (int)width, (int)height);


		pLevel->AddComponent(pCol);
		pLevel->AddComponent(pTex);
		return pLevel;
	}
};