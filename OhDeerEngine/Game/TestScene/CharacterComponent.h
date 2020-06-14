#pragma once
#include <BaseComponent.h>
class OhDeer::Command;
class CharacterComponent :
    public OhDeer::BaseComponent
{
    enum State {
        IDLE,
        RUNNINGLEFT,
        RUNNINGRIGHT,
        JUMPING,
        ATTACKING
    };


public:
    CharacterComponent();
    virtual void Update(float) override;
    virtual void Initialize() override;

    void Jump();
    void Attack();
protected:


};

