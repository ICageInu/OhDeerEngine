#pragma once
#include "Observer.h"
namespace OhDeerEngine
{
	class BaseCharComponent;
	class HealthObserver : public Observer
	{
	public:
		HealthObserver() = default;
		virtual ~HealthObserver() override;
		virtual void OnNotify(const BaseCharComponent& baseChar) override;

	private:

	};


}