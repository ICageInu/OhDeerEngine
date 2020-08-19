#include "BaseEnemyComponent.h"
#include "TransformComponent.h"

BaseEnemyComponent::BaseEnemyComponent(OhDeerEngine::GameObject* pPlayer, OhDeerEngine::GameObject* pParent, OhDeerEngine::RenderComponent* pTexture, OhDeerEngine::CollisionComponent* pCollider, CharType chartype) :
	BaseCharComponent(pParent, pTexture, pCollider, chartype),
	m_pPlayer{ pPlayer }
{
}

void BaseEnemyComponent::SpecificUpdate(const float deltaT)
{
	//TODO place the logic here for moving towards the player
	const glm::vec2 playerPos = m_pPlayer->GetTransform()->GetPosition();


}