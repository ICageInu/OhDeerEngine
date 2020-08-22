#pragma once
#include <vector>

namespace OhDeerEngine
{
	class GameObject;
	class Observer;
	class Subject
	{
	public:
		Subject() = default;
		virtual ~Subject();


		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

		Subject* operator=(Subject& other);

		std::vector<GameObject*>Objects;
		std::vector<Observer*>Observers;

		void RegisterObserver(Observer* pObserver);
		bool UnRegisterObserver(Observer* pObserver);
		void NotifyAllObservers(const uint8_t event);
	};


}