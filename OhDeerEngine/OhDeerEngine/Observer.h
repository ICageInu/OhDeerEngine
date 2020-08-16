#pragma once
namespace OhDeerEngine
{
	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void OnNotify() = 0;
	};
}