#pragma once
#include "OhDeerEngine.h"
class MainGame : public OhDeer::OhDeerEngine
{
public:
	MainGame();
	~MainGame() = default;
protected:
	virtual void Initialize() override;

};

