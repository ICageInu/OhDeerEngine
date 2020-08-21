#pragma once
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "Commands.h"
#include "EnemyComponent.h"
#include "HealthObserver.h"
#include "ScoreObserver.h"
#include "Subject.h"
#include <array>
#include "Structs.h"
#include "HighscoreParser.h"
#include "InputComponent.h"
#include "PickupComponent.h"
#include "TransformComponent.h"
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

			if (ob2->GetTag() == "Emerald")
			{
				ob2->SetEnabledDisabled(false);
				OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('e');
			}

			if (ob2->GetComponent<EnemyComponent>())
			{
				OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('-');
			}
			if (ob2->GetComponent<PickupComponent>())
			{
				ob2->GetComponent<OhDeerEngine::CollisionComponent>()->EnableStatic(false);
			}

		};
		pPlayer->SetOnTriggerCallBack(lambdaTrigger);
		auto pPlayerComp = new PlayerComponent(pPlayer, pPlayerTexture, pPlayerCol, true);
		pPlayerComp->SetKeyboardKeys(SDLK_w, SDLK_s, SDLK_d, SDLK_a);
		pPlayerComp->BindActionA(new ActionOneCommand());

		return pPlayer;
	}

	inline OhDeerEngine::GameObject* MakeNobbin(const glm::vec2& pos, float width, float height)
	{
		OhDeerEngine::GameObject* pNobbin = new OhDeerEngine::GameObject();



		return pNobbin;
	}

	inline void MakeLevel(OhDeerEngine::Scene* pScene, const glm::vec2& pos, float width, float height)
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

		auto pPickupComp = new PickupComponent();

		auto pCol = new OhDeerEngine::CollisionComponent(pos, width, height, true);
		auto pTex = new OhDeerEngine::RenderComponent();
		pTex->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("Gold.png"), (int)width, (int)height);
		pCol->EnableTrigger(true);
		pCol->EnableStatic(true);
		auto lambdaTrigger = [](OhDeerEngine::GameObject* ob1, OhDeerEngine::GameObject* ob2, OhDeerEngine::GameObject::TriggerAction)
		{
			//TODO MAKE THIS ACTUALLY DO SOMETHING GOOD
		};
		pMoneyBag->SetOnTriggerCallBack(lambdaTrigger);
		pMoneyBag->AddComponent(pCol);
		pMoneyBag->AddComponent(pTex);
		pMoneyBag->AddComponent(pPickupComp);
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
		fps->Initialize(OhDeerEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24));
		return pFps;
	}


	inline void MakeStartScreen(OhDeerEngine::Scene* pScene)
	{
		//so we got top 10 highscores
		//players also need to be able to insert their initials

		//first we make the 10 highscore objects
		const float height = OhDeerEngine::ServiceLocator::GetGameHandlers()->windowDimensions.y / 15.f;
		const float width = height;

		OhDeerEngine::Font* pFont = OhDeerEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 48);

		//read in highscores
		std::array<std::string, 10>scores{ {} };
		std::array<std::string, 10>names{ {} };
		Highscore highscore;

		highscore.ParseFile("./Resources/highscores.txt", scores, names);

		//setting up the scores + initials
		for (size_t i = 0; i < 10; i++)
		{
			auto pTempObjScore = new OhDeerEngine::GameObject({ width,height + height * i });
			auto pTempObjName = new OhDeerEngine::GameObject({ width * 6,height + height * i });


			auto pScoreObj = new OhDeerEngine::TextComponent();
			auto pNameObj = new OhDeerEngine::TextComponent();
			if (scores[i] != "")
			{
				pScoreObj->SetText(scores[i]);
				pNameObj->SetText(names[i]);
			}
			else
			{
				pScoreObj->SetText("0000000");

				pNameObj->SetText("-----");
			}
			pScoreObj->AddFont(pFont);
			pNameObj->AddFont(pFont);

			pTempObjScore->AddComponent(pScoreObj);
			pTempObjName->AddComponent(pNameObj);
			pScene->Add(pTempObjScore);
			pScene->Add(pTempObjName);
		}


		//making it so that a player can give in their name
		auto pTempObj = new OhDeerEngine::GameObject({ OhDeerEngine::ServiceLocator::GetGameHandlers()->windowDimensions.x - width * 2,height * 5 });
		auto pTextComp = new OhDeerEngine::TextComponent();
		pTextComp->AddFont(pFont);
		pTextComp->SetText("...");
		auto pInputComp = new InputComponent(pTextComp);
		pTempObj->AddComponent(pInputComp);
		pTempObj->AddComponent(pTextComp);
		pScene->Add(pTempObj);
	}
};