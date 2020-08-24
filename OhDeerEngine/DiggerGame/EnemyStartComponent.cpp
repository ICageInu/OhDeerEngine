#include "EnemyStartComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Factory.h"
EnemyStartComponent::EnemyStartComponent(int amountEnemies, float enemyWidth, float enemyHeight) :
	m_SpawnTimerMax{ 4.0f },
	m_SpawnTimer{ m_SpawnTimerMax },
	m_EnemyWidth{ enemyWidth },
	m_EnemyHeight{ enemyHeight },
	m_AmountEnemies{ amountEnemies }
{

}

void EnemyStartComponent::Update(const float deltaT)
{

	if (m_SpawnTimer < 0 && m_AmountEnemies > 0)
	{
		m_SpawnTimer = m_SpawnTimerMax;
		m_AmountEnemies--;
		SpawnEnemy();
	}
	else m_SpawnTimer -= deltaT;
}

int EnemyStartComponent::GetAmountEnemies() const
{
	return m_AmountEnemies;
}

void EnemyStartComponent::SpawnEnemy()
{
	Factory factory;
	for (auto pObj : OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->GetObjects())
	{
		if (pObj->GetComponent<PlayerComponent>())
		{
			OhDeerEngine::SceneManager::GetInstance().GetActiveScene()->Add(factory.MakeNobbin(pObj,m_pParent->GetTransform()->GetPosition(), m_EnemyWidth, m_EnemyHeight));
			break;
		}
	}
}
