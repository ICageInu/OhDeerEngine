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
#include "EnemyStartComponent.h"
#include "TransformComponent.h"
#include "FPSComponent.h"
#include "Scene.h"
#include "CommandsOverrides.h"
#include "FireBallComponent.h"
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
		auto pPlayerCol = new OhDeerEngine::CollisionComponent(pos, width, height, {}, true);
		auto pPlayerComp = new PlayerComponent(pPlayer, pPlayerTexture, pPlayerCol);
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


			if (ob2->GetComponent<PickupComponent>())
			{
				auto colComp = ob2->GetComponent<OhDeerEngine::CollisionComponent>();
				if (colComp->GetIsStatic())
					colComp->EnableStatic(false);

			}

		};
		pPlayer->SetOnTriggerCallBack(lambdaTrigger);

		pPlayerComp->SetKeyboardKeys(SDLK_w, SDLK_s, SDLK_d, SDLK_a);
		pPlayerComp->SetKeyboardActions(SDLK_SPACE, NULL, NULL, NULL);
		pPlayerComp->BindActionA(new ActionOneCommand());

		return pPlayer;
	}

	inline OhDeerEngine::GameObject* MakeNobbin(OhDeerEngine::GameObject* pPlayer, const glm::vec2& pos, float width, float height)
	{
		const float objWidth{ width - width / 4.f };
		const float objHeight{ height - height / 4.f };
		OhDeerEngine::GameObject* pNobbin = new OhDeerEngine::GameObject(pos);
		pNobbin->SetTag("enemy");
		auto pEnemyTexture = new OhDeerEngine::RenderComponent();
		pEnemyTexture->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("hobbin.png"), (int)objWidth, (int)objHeight);
		//pPlayerTexture->AddRectangleToDraw(150, 150);
		const glm::vec2 colOffset{ width / 8.f, height / 4.0f };

		auto pEnemyCol = new OhDeerEngine::CollisionComponent(pos, objWidth, objHeight, {}, true);
		auto pEnemyComp = new EnemyComponent(pPlayer, pNobbin, pEnemyTexture, pEnemyCol);
		auto lambdaTrigger = [&pEnemyComp](OhDeerEngine::GameObject* ob1, OhDeerEngine::GameObject* ob2, OhDeerEngine::GameObject::TriggerAction)
		{
			if (!ob2->IsActive)return;




			if (ob2->GetComponent<PlayerComponent>())
			{
				OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('-');
				ob2->GetComponent<PlayerComponent>()->Respawn();
			}

		};
		pNobbin->SetOnTriggerCallBack(lambdaTrigger);


		return pNobbin;
	}

	inline void AddLevel(OhDeerEngine::Scene* pScene, const glm::vec2& pos, float width, float height)
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
				auto pCol = new OhDeerEngine::CollisionComponent(posObj, widthObj, heightObj,{}, true);
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
		auto pCol = new OhDeerEngine::CollisionComponent(pos, width, height,{}, true);
		pCol->EnableStatic(true);
		auto pTex = new OhDeerEngine::RenderComponent();
		pTex->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("emerald.png"), (int)width, (int)height);


		pEmerald->AddComponent(pCol);
		pEmerald->AddComponent(pTex);
		return pEmerald;
	}

	inline void AddMoneyBag(OhDeerEngine::Scene* pScene, const glm::vec2& pos, float width, float height)
	{
		OhDeerEngine::GameObject* pMoneyBag = new OhDeerEngine::GameObject(pos);
		pMoneyBag->SetTag("MoneyBag");

		auto pPickupComp = new PickupComponent();

		auto pCol = new OhDeerEngine::CollisionComponent(pos, width, height, {}, true);
		auto pTex = new OhDeerEngine::RenderComponent();
		pTex->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("Gold.png"), (int)width, (int)height);

		auto lambdaTrigger = [pCol, pPickupComp](OhDeerEngine::GameObject* ob1, OhDeerEngine::GameObject* ob2, OhDeerEngine::GameObject::TriggerAction)
		{
			//TODO MAKE THIS ACTUALLY DO SOMETHING GOOD
			//when not static anymore, check below, if nothing below start falling
			//the static thing we check in the function checking for collision
			//we check if the point is in any rectangle, if not we just let it fall
			//pass point underneath obj
			auto rect = pCol->GetCollision();
			const glm::vec2 point{ rect->x + rect->w / 2.0f, rect->y - rect->h / 2.0f };
			if (!pPickupComp->IsFalling)
			{
				if (point.y > 0 || !pCol->IsPointInRect(point, ob2->GetComponent<OhDeerEngine::CollisionComponent>()->GetCollision()))
				{
					pPickupComp->IsFalling = true;
				}
			}
			else if (pPickupComp->IsFalling)
			{
				//if falling and hit player kill player
				//if falling and hit enemy kill enemy
				//if falling and hit anything turn into pickupable
				if (ob2->GetComponent<PlayerComponent>())
				{
					OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('-');
					//ob2->GetComponent<OhDeerEngine::CollisionComponent>()->EnableStatic(false);
				}
				if (ob2->GetComponent<EnemyComponent>())
				{
					OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('n');
					ob2->IsActive = false;
				}

				if (point.y - 4.0f < 0 || pCol->IsOverlapping(ob2->GetComponent<OhDeerEngine::CollisionComponent>()))
				{
					pPickupComp->IsFalling = false;
					pPickupComp->IsPickup = true;
				}

			}
			else
			{
				if (ob2->GetComponent<PlayerComponent>())
				{
					OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('-');
					ob1->IsActive = false;
				}
				if (ob2->GetComponent<EnemyComponent>())
				{
					ob1->IsActive = false;
				}
			}


		};
		pMoneyBag->SetOnTriggerCallBack(lambdaTrigger);
		pMoneyBag->AddComponent(pCol);
		pMoneyBag->AddComponent(pTex);
		pMoneyBag->AddComponent(pPickupComp);
		pScene->Add(pMoneyBag);
		//first add to scene, then set as static to still have these objects be in the correct container
		pCol->EnableStatic(true);
	}

	inline OhDeerEngine::GameObject* MakeEnemyStart(const glm::vec2& pos, float width, float height, int amountEnemies)
	{
		OhDeerEngine::GameObject* pStart = new OhDeerEngine::GameObject(pos);
		pStart->SetTag("EnemyStart");
		auto pEnemyStartComp = new EnemyStartComponent(amountEnemies, width, height);
		pStart->AddComponent(pEnemyStartComp);
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
		auto pTempObj = new OhDeerEngine::GameObject({ OhDeerEngine::ServiceLocator::GetGameHandlers()->windowDimensions.x - width * 4,height * 5 });
		auto pTextComp = new OhDeerEngine::TextComponent();
		pTextComp->AddFont(pFont);
		pTextComp->SetText("...");
		auto pInputComp = new InputComponent(pTextComp);
		pTempObj->AddComponent(pInputComp);
		pTempObj->AddComponent(pTextComp);
		pScene->Add(pTempObj);
	}


	inline OhDeerEngine::GameObject* MakeFireBall(const glm::vec2& pos,const glm::vec2& dir, float width, float height)
	{
		const glm::vec2 colOffset{ width / 4.f, height / 4.f };
		OhDeerEngine::GameObject* pFireBall = new OhDeerEngine::GameObject(pos+ colOffset);
		pFireBall->SetTag("FireBallShot");
		const float colWidth{ width - width / 2.f };
		const float colHeight{ height - height / 2.f };
		auto pCol = new OhDeerEngine::CollisionComponent(pos, colWidth, colHeight, {}, true);
		auto pTex = new OhDeerEngine::RenderComponent();
		auto pFireBallComp = new FireBallComponent(dir);
		pTex->SetTexture(OhDeerEngine::ResourceManager::GetInstance().LoadTexture("fireball.png"), 
			(int)colWidth, (int)colHeight/*,colOffset*/);
		auto lambdaTrigger = [](OhDeerEngine::GameObject* ob1, OhDeerEngine::GameObject* ob2, OhDeerEngine::GameObject::TriggerAction)
		{
			if (!ob2->IsActive) return;
			if (ob2->GetTag() == "Level")
			{
				ob1->SetEnabledDisabled(false);
			}
			if (ob2->GetComponent<EnemyComponent>())
			{
				OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Subject->NotifyAllObservers('n');
				ob2->IsActive = false;
			}
		};
		pFireBall->SetOnTriggerCallBack(lambdaTrigger);
		pFireBall->AddComponent(pCol);
		pFireBall->AddComponent(pFireBallComp);
		pFireBall->AddComponent(pTex);

		return pFireBall;
	}
};