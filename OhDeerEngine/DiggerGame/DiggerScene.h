#pragma once
#include "Scene.h"

class DiggerScene :
    public OhDeerEngine::Scene
{
public:
    DiggerScene(const std::string& sceneName);

    void Initialize()override;
    void Update(float deltaT) override;
private:
    OhDeerEngine::GameObject* m_pFPSCounter;
    //debug Frame
    float m_SecondsTimer{};
    int m_FrameCounter{};
};

