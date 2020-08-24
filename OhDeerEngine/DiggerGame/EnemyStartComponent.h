#pragma once
#include <BaseComponent.h>
class EnemyStartComponent :
    public OhDeerEngine::BaseComponent
{
public:
	EnemyStartComponent(int amountEnemies,float enemyWidth,float enemyHeight);

	EnemyStartComponent(const EnemyStartComponent& other) = delete;
	EnemyStartComponent(EnemyStartComponent&& other) = delete;
	EnemyStartComponent& operator=(const EnemyStartComponent& other) = delete;
	EnemyStartComponent& operator=(EnemyStartComponent&& other) = delete;

	virtual void Update(const float deltaT) override;
	virtual void Render() const override {};
	virtual void FixedUpdate(const float deltaT) override {};

	int GetAmountEnemies()const;

private:
	const float m_SpawnTimerMax;
	float m_SpawnTimer;
	float m_EnemyWidth, m_EnemyHeight;
	int m_AmountEnemies;
	void SpawnEnemy();
};

