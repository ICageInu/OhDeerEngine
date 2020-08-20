#pragma once
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "Commands.h"
#include "BaseEnemyComponent.h"
#include "HealthObserver.h"
#include "ScoreObserver.h"


class Factory
{
public:
	inline OhDeerEngine::GameObject* MakePlayer(const glm::vec2& pos, float width, float height)
	{
		OhDeerEngine::GameObject* pPlayer = new OhDeerEngine::GameObject(pos);
		pPlayer->SetTag("player");
		auto pPlayerTexture = new OhDeerEngine::RenderComponent();
		pPlayerTexture->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("digger.png"), (int)width, (int)height);
		//pPlayerTexture->AddRectangleToDraw(150, 150);
		auto pPlayerCol = new OhDeerEngine::CollisionComponent(pos, width, height, true);
		pPlayerCol->EnableTrigger(true);
		auto lambdaTrigger = [](OhDeerEngine::GameObject* ob1, OhDeerEngine::GameObject* ob2, OhDeerEngine::GameObject::TriggerAction)
		{
			if (!ob2->IsActive)return;
			if (ob2->GetTag() == "Level")
			{
				ob2->SetEnabledDisabled(false);
			}

			if (ob2->GetTag()=="Emerald")
			{
				ob2->SetEnabledDisabled(false);
				OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('e');
			}


		};
		pPlayer->SetOnTriggerCallBack(lambdaTrigger);
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

	inline void MakeLevel(OhDeerEngine::Scene* pScene,const glm::vec2& pos, float width, float height)
	{
		//numbers go from topleft to bottomright
		const float widthObj = std::ceilf(width / 3.f);
		const float heightObj = std::ceilf(height / 3.f);

		const std::string png{ ".png" };

		//vert
		for (size_t i = 0; i < 3; i++)
		{
			//horz
			for (size_t j = 0; j < 3; j++)
			{

				glm::vec2 posObj{ pos.x + j * widthObj,pos.y + i * heightObj };

				OhDeerEngine::GameObject* pLevel = new OhDeerEngine::GameObject(posObj);
				//textures
				auto pTex = new OhDeerEngine::RenderComponent();
				pTex->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("wall" + std::to_string(i + 1) + std::to_string(j + 1) + png), (int)widthObj, (int)heightObj);

				//collisions
				auto pCol = new OhDeerEngine::CollisionComponent(posObj, widthObj, heightObj, true);
				pCol->EnableStatic(true);

				pLevel->AddComponent(pCol);
				pLevel->AddComponent(pTex);
				pLevel->SetTag("Level");
				pScene->Add(pLevel);

			}
		}
	}

	inline OhDeerEngine::GameObject* MakeEmerald(const glm::vec2& pos, float width, float height)
	{
		OhDeerEngine::GameObject* pEmerald = new OhDeerEngine::GameObject(pos);
		pEmerald->SetTag("Emerald");
		auto pCol = new OhDeerEngine::CollisionComponent(pos, width, height, true);
		pCol->EnableStatic(true);
		auto pTex = new OhDeerEngine::RenderComponent();
		pTex->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("emerald.png"), (int)width, (int)height);


		pEmerald->AddComponent(pCol);
		pEmerald->AddComponent(pTex);
		return pEmerald;
	}

	inline OhDeerEngine::GameObject* MakeMoneyBag(const glm::vec2& pos, float width, float height)
	{
		OhDeerEngine::GameObject* pMoneyBag = new OhDeerEngine::GameObject(pos);
		pMoneyBag->SetTag("MoneyBag");
		auto pCol = new OhDeerEngine::CollisionComponent(pos, width, height, true);
		auto pTex = new OhDeerEngine::RenderComponent();
		pTex->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("Gold.png"), (int)width, (int)height);


		pMoneyBag->AddComponent(pCol);
		pMoneyBag->AddComponent(pTex);
		return pMoneyBag;
	}

	inline OhDeerEngine::GameObject* MakeEnemyStart(const glm::vec2& pos, float width, float height)
	{
		OhDeerEngine::GameObject* pStart = new OhDeerEngine::GameObject(pos);
		pStart->SetTag("EnemyStart");

		return pStart;
	}

	inline OhDeerEngine::GameObject* MakeFPS()
	{
		OhDeerEngine::GameObject* pFps = new OhDeerEngine::GameObject();

		auto fps = new OhDeerEngine::FPSComponent();
		pFps->AddComponent(fps);
		fps->Initialize(OhDeerEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf",24));
		return pFps;
	}

};