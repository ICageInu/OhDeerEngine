#pragma once
#include "Observer.h"
namespace OhDeerEngine
{
	class HealthObserver : public Observer
	{
	public:
		HealthObserver() = default;
		virtual ~HealthObserver() override;
		virtual void OnNotify() override;

	private:

	};


}