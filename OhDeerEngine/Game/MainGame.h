#pragma once
#include "OhDeerEngine.h"
class MainGame : public OhDeerEngine
{
public:
	MainGame();
	~MainGame() = default;
protected:
	virtual void Initialize() override;

};

