#pragma once
#include "PlayerComponent.h"

namespace OhDeerEngine
{
	
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(PlayerComponent* pPlayerComp) = 0;
	};

	class JumpCommand : public Command
	{
	public:
		virtual void Execute(PlayerComponent* pPlayerComp) override
		{
			pPlayerComp->Jump();
		}
	};

	class ActionOneCommand : public Command
	{
	public:
		virtual void Execute(PlayerComponent* pPlayerComp) override
		{
			pPlayerComp->ActionOne();
		}
	};
	class ActionTwoCommand : public Command
	{
	public:
		virtual void Execute(PlayerComponent* pPlayerComp) override
		{
			pPlayerComp->ActionTwo();
		}
	};
	class ActionThreeCommand : public Command
	{
	public:
		virtual void Execute(PlayerComponent* pPlayerComp) override
		{
			pPlayerComp->ActionThree();
		}
	};
	class ActionFourCommand : public Command
	{
	public:
		virtual void Execute(PlayerComponent* pPlayerComp) override
		{
			pPlayerComp->ActionFour();
		}
	};
}