#include "OhDeerPCH.h"
#include "BaseCharComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "Observer.h"

OhDeerEngine::BaseCharComponent::BaseCharComponent(GameObject* pParent, RenderComponent* pTexture, CollisionComponent* pCollider, CharType chartype) :
	m_PosNextFrame{},
	m_pCollision{ pCollider },
	m_pTexture{ pTexture },
	m_ScoreOnDeath{ 0 },
	m_CharType{ chartype }
{
	m_MovementSpeed = 50;
	pParent->AddComponent(this);
	pParent->AddComponent(pTexture);
	pParent->AddComponent(pCollider);
}
void OhDeerEngine::BaseCharComponent::Update(const float deltaT)
{
	SpecificUpdate(deltaT);
	Move();
}

void OhDeerEngine::BaseCharComponent::Render() const {}

void OhDeerEngine::BaseCharComponent::FixedUpdate(const float) {}

int OhDeerEngine::BaseCharComponent::GetScoreToAdd() const
{
	return m_ScoreOnDeath;
}

int OhDeerEngine::BaseCharComponent::GetCharacterType() const
{
	return m_CharType;
}

void OhDeerEngine::BaseCharComponent::SetScoreWorth(int score)
{
	m_ScoreOnDeath = score;
}

void OhDeerEngine::BaseCharComponent::RegisterObserver(Observer* pObserver)
{
	for (Observer* pObs : m_Observers)
	{

		if (typeid(*pObs) == typeid(*pObserver))
		{
			throw std::exception("RegisterObserver: This component already exists");
		}
	}
	m_Observers.push_back(pObserver);
}

bool OhDeerEngine::BaseCharComponent::UnRegisterObserver([[maybe_unused]] Observer* pObserver)
{
	auto it = std::find_if(m_Observers.cbegin(), m_Observers.cend(), [pObserver](Observer* pObs)
		{
			return typeid(*pObs) == typeid(*pObserver);
		});
	if (it != m_Observers.cend())
	{
		m_Observers.erase(it);
		return true;
	}
	return false;
}

void OhDeerEngine::BaseCharComponent::NotifyAllObservers()
{
	for (Observer* pObs : m_Observers)
	{
		pObs->OnNotify(*this);
	}
}

void OhDeerEngine::BaseCharComponent::Move()
{
	m_pParent->GetTransform()->SetPosition(m_PosNextFrame);

}
