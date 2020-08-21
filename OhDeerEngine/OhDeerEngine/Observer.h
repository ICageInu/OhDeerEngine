#pragma once
//to make your eyes bleed
//https://stackoverflow.com/questions/644629/base-enum-class-inheritance
namespace OhDeerEngine
{
	class BaseCharComponent;
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() {};
		virtual void OnNotify(const char eventType=0) = 0;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
	};
}