//EventListener.cpp

#include "EventListener.h"

#include "EventSystem.h"
#include "Event.h"

EventListener::EventListener()
{
    //
}

EventListener::~EventListener()
{
    //
}

void EventListener::SetRegistrationActive(EventSystem* pEventSystem)
{
    m_pEventSystem = pEventSystem;
    m_registered = true;
}