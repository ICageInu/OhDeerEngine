#pragma once
//to make your eyes bleed
//https://stackoverflow.com/questions/644629/base-enum-class-inheritance
namespace OhDeerEngine
{
	class BaseCharComponent;
	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void OnNotify(const BaseCharComponent& baseChar/*,uint8_t eventType=0*/) = 0;
	};
}