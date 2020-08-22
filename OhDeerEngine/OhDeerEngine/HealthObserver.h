#pragma once
#include "Observer.h"
#include <vector>
#include <array>
#include "RenderComponent.h"

class HealthObserver : public OhDeerEngine::Observer
{
public:
	HealthObserver(const std::array<OhDeerEngine::RenderComponent*, 5>& rendercomps);
	//virtual ~HealthObserver() override;
	virtual void OnNotify(const char eventType) override;

	HealthObserver(const HealthObserver& other) = delete;
	HealthObserver(HealthObserver&& other) = delete;
	HealthObserver& operator=(const HealthObserver& other) = delete;
	HealthObserver& operator=(HealthObserver&& other) = delete;

private:
	std::array<OhDeerEngine::RenderComponent*, 5> m_Lives{};
	int m_AmountHealth{ 3 };
};

