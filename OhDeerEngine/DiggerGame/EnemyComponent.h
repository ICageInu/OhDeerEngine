#pragma once
#include <BaseCharComponent.h>
#include "GameObject.h"
#include "glm/vec2.hpp"

class EnemyComponent :
    public OhDeerEngine::BaseCharComponent
{

    enum class AngerState
    {
        Kalm,
        Panik
    };

public:
 
    EnemyComponent(OhDeerEngine::GameObject* pPlayer,OhDeerEngine::GameObject* pParent, OhDeerEngine::RenderComponent* pTexture, OhDeerEngine::CollisionComponent* pCollider, CharType chartype = CharType::Enemy);
    void SetPlayer(OhDeerEngine::GameObject* pPlayer);

    virtual void ActionOne() override {};
    virtual void ActionTwo() override {};
    virtual void ActionThree() override {};
    virtual void ActionFour() override {};
private:
    virtual void SpecificUpdate(const float deltaT) override;

    OhDeerEngine::GameObject* m_pPlayer;
    const float m_AngerIssuesMax;
    float m_AngerIssues;
    AngerState m_State;
    bool m_WasMovingDown;
};

