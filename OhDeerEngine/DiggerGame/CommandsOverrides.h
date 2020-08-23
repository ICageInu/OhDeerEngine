#pragma once
#include "PlayerComponent.h"
#include "Commands.h"


class ActionOneCommand : public OhDeerEngine::Command
{
public:
	virtual void Execute(OhDeerEngine::BaseCharComponent* pPlayerComp) override
	{
		pPlayerComp->ActionOne();
	}
};
class ActionTwoCommand : public OhDeerEngine::Command
{
public:
	virtual void Execute(OhDeerEngine::BaseCharComponent* pPlayerComp) override
	{
		pPlayerComp->ActionTwo();
	}
};
class ActionThreeCommand : public OhDeerEngine::Command
{
public:
	virtual void Execute(OhDeerEngine::BaseCharComponent* pPlayerComp) override
	{
		pPlayerComp->ActionThree();
	}
};
class ActionFourCommand : public OhDeerEngine::Command
{
public:
	virtual void Execute(OhDeerEngine::BaseCharComponent* pPlayerComp) override
	{
		pPlayerComp->ActionFour();
	}
};