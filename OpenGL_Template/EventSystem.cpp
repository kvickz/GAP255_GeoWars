//EventSystem.cpp

#include "EventSystem.h"

#include "Event.h"
#include "EventListener.h"

#include "Macros.h"

EventSystem::EventSystem()
{

}

EventSystem::~EventSystem()
{
    
}

void EventSystem::RegisterListener(const EventID& eventID, EventListener* pEventListener)
{
    m_listeners[eventID].push_back(pEventListener);
    pEventListener->SetRegistrationActive(this);
}

void EventSystem::RemoveListener(const EventID& eventID, EventListener* pEventListener)
{
    auto findIt = m_listeners.find(eventID);
    if (findIt == m_listeners.end())
        return;
    
    EventListenerList& eventListenerList = findIt->second;
    eventListenerList.remove(pEventListener);
}

void EventSystem::TriggerEvent(Event* pEvent)
{
    auto findIt = m_listeners.find(pEvent->GetEventID());
    if (findIt == m_listeners.end())
        return;

    for (auto* pEventListener : findIt->second)
    {
        pEventListener->OnEvent(pEvent);
    }

    SAFE_DELETE(pEvent);
}