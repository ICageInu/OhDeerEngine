#pragma once
#include <BaseCharComponent.h>
#include "GameObject.h"



class EnemyComponent :
    public OhDeerEngine::BaseCharComponent
{
public:
    EnemyComponent(OhDeerEngine::GameObject* pPlayer,OhDeerEngine::GameObject* pParent, OhDeerEngine::RenderComponent* pTexture, OhDeerEngine::CollisionComponent* pCollider, CharType chartype = CharType::Enemy);

private:
    virtual void SpecificUpdate(const float deltaT) override;

    OhDeerEngine::GameObject* m_pPlayer;
};

