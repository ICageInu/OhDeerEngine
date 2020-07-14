#pragma once
#include <OhDeer.h>
class MainGame :
    public OhDeerEngine::OhDeer
{
public:
    void LoadGame()const override;
};

