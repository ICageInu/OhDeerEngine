#include "OhDeerPCH.h"
#include "Subject.h"
#include "GameObject.h"
#include "Observer.h"



OhDeerEngine::Subject::~Subject()
{
	//since all of this is shared, might as well just make it so that it only deletes it once, that way it can just yeet out of here
	//if these are already deleted and we just need to delete the pointed of subject anyways
	for (auto pObs : Observers)
	{
		SafeDelete(pObs);
	}
	for (auto pObj : Objects)
	{
		SafeDelete(pObj);
	}
}



//
//OhDeerEngine::Subject::Subject(const Subject& other) noexcept :
//	Observers{other.Observers},
//	Objects{ other.Objects }
//{
//	//other.Observers.clear();
//	//other.Objects.clear();
//}
//
//OhDeerEngine::Subject::Subject(Subject&& other) noexcept :
//	Observers{ other.Observers },
//	Objects{ other.Objects }
//{
//	other.Observers.clear();
//	other.Objects.clear();
//}

//OhDeerEngine::Subject& OhDeerEngine::Subject::operator=(Subject&& other) noexcept
//{
//	if (this != &other)// no self assignment
//	{
//		Objects = other.Objects;
//		Observers = other.Observers;
//
//		other.Objects.clear();
//		other.Observers.clear();
//	}
//	return *this;
//}



OhDeerEngine::Subject* OhDeerEngine::Subject::operator=(Subject& other)
{
	if (this != &other)// no self assignment
	{
		Objects = other.Objects;
		Observers = other.Observers;

		other.Objects.clear();
		other.Observers.clear();
	}
	return this;
}

void OhDeerEngine::Subject::RegisterObserver(Observer* pObserver)
{
	for (Observer* pComp : Observers)
	{

		if (typeid(*pComp) == typeid(*pObserver))
		{
			throw std::exception("RegisterObserver: This observer already exists");
		}
	}
	Observers.push_back(pObserver);
}

bool OhDeerEngine::Subject::UnRegisterObserver(Observer* pObserver)
{
	auto it = std::find_if(Observers.cbegin(), Observers.cend(), [pObserver](Observer* pObs)
		{
			return typeid(*pObs) == typeid(*pObserver);
		});
	if (it != Observers.cend())
	{
		Observers.erase(it);
		return true;
	}
	return false;
}

void OhDeerEngine::Subject::NotifyAllObservers(const uint8_t event)
{
	for (Observer* pObs : Observers)
	{
		pObs->OnNotify(event);
	}
}