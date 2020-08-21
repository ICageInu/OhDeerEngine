#pragma once
#include <BaseComponent.h>
class PickupComponent :
    public OhDeerEngine::BaseComponent
{
public:
	virtual void Update(const float deltaT) override;
	virtual void Render() const override {};
	virtual void FixedUpdate(const float deltaT) override {};
	bool IsFalling{ false }, IsPickup{ false };
};

