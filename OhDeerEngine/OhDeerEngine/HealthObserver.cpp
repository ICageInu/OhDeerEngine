#include "HealthObserver.h"
#include "HealthObserver.h"

OhDeerEngine::HealthObserver::~HealthObserver()
{
}

//there will be a couple different eventTypes,just to make it so that we can differentiate between what's picked up
//use first letter of the event
void OhDeerEngine::HealthObserver::OnNotify(const char eventType)
{
	switch (eventType)
	{
	case '+':

		break;
	case '-':

		break;
	}

}
