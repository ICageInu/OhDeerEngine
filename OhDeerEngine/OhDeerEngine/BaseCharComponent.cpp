#include "OhDeerPCH.h"
#include "BaseCharComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"

OhDeerEngine::BaseCharComponent::BaseCharComponent(GameObject* pParent, RenderComponent* pTexture, CollisionComponent* pCollider):
	m_PosNextFrame{},
	m_pCollision{pCollider},
	m_pTexture{pTexture}
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

void OhDeerEngine::BaseCharComponent::Render() const{}

void OhDeerEngine::BaseCharComponent::FixedUpdate(const float){}

void OhDeerEngine::BaseCharComponent::Move()
{
	m_pParent->GetTransform()->SetPosition(m_PosNextFrame);

}
