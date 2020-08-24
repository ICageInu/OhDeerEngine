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
    virtual void FixedUpdate(const float deltaT)override;
    virtual void ActionOne() override;
    virtual void ActionTwo() override {};
    virtual void ActionThree() override {};
    virtual void ActionFour() override {};
    bool IsAngry{ false };
private:
    OhDeerEngine::GameObject* m_pPlayer;
    const float m_AngerIssuesMax;
    const float m_AngerIssuesDurationMax;
    float m_AngerIssues;
    float m_AngerIssuesDurationLeft;
    AngerState m_State;
    const float m_SeekerTimerMax;
    float m_SeekerTimer;
    bool m_IsControlled;

    virtual void SpecificUpdate(const float deltaT) override;
    void AILogicCalm(const float deltaT);
    void AILogicAngry(const float deltaT);
    void PlayerControled(const float deltaT);
};

