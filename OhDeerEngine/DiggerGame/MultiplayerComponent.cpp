#include "OhDeerPCH.h"
#include "MultiplayerComponent.h"
#include "InputManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
MultiplayerComponent::MultiplayerComponent() :
	m_pPlayer{ nullptr },
	m_IsControllingEnemy{},
	m_FoundPlayer{}
{
}

void MultiplayerComponent::Update(const float deltaT)
{
	if (!m_FoundPlayer)
	{
		auto obs = OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->GetKinematicCollisions();

		for (size_t i = 0; i < obs.size(); i++)
		{
			if (obs[i]->GetParent()->GetComponent<PlayerComponent>())
			{
				m_pPlayer = obs[i]->GetParent()->GetComponent<PlayerComponent>();
				break;
			}
		}
	}
	if (!m_IsControllingEnemy)
	{
		if (m_pPlayer->GetIsConnectedWithController())
		{

		}
		else if (OhDeerEngine::InputManager::GetInstance().Connected())
		{
			if (OhDeerEngine::InputManager::GetInstance().AnyButtonPressed())
			{
				std::vector<EnemyComponent*> enemies;
				auto obs = OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->GetKinematicCollisions();

				for (size_t i = 0; i < obs.size(); i++)
				{
					if (obs[i]->GetParent()->GetComponent<EnemyComponent>())
					{
						enemies.push_back(obs[i]->GetParent()->GetComponent<EnemyComponent>());
					}
				}
				//now we select random enemy and give control
				int number = std::rand() % enemies.size();

				enemies[number]->SetIsControlled(true);
				enemies[number]->SetIsControlledWithController(true);
				m_IsControllingEnemy = true;
			}
		}
	}
}

void MultiplayerComponent::PlayerDied()
{
	m_IsControllingEnemy = false;
}
