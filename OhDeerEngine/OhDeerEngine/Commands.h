#pragma once
#include "BaseCharComponent.h"
namespace OhDeerEngine
{

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute(BaseCharComponent* pPlayerComp) = 0;
};
}