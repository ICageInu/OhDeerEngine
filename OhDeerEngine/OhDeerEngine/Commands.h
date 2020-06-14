#pragma once
#include "pch.h"
#include "../Game/TestScene/CharacterComponent.h"

namespace OhDeer {

	//TODO aight so we be making use of command pattern here
	//figure out how to implement this decently
	//think about order you push these into the inputmanager
	class Command {
	public:
		virtual ~Command() {};
		virtual void Execute([[maybe_unused]] CharacterComponent* pPlayer) = 0;
	};


    class JumpCommand : public Command {
    public:
        virtual void Execute(CharacterComponent* pPlayer) override
        {
            pPlayer->Jump();
        };
    };
    class ActionOneCommand : public Command {
    public:
        virtual void  Execute(CharacterComponent* pPlayer) override
        {
            pPlayer->Attack();
        };
    };



}