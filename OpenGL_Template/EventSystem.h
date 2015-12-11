//EventSystem.h

#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include "Constants.h"

#include <unordered_map>
#include <list>
#include <queue>

class Event;
class EventListener;

class EventSystem
{
private:
    typedef std::list<EventListener*> EventListenerList;
    std::unordered_map<EventID, EventListenerList> m_listeners;
    //std::queue<Event*> m_eventQueue;  //TODO: Deferred events

public:
    EventSystem();
    ~EventSystem();

    void RegisterListener(const EventID& eventID, EventListener* pEventListener);
    void RemoveListener(const EventID& eventID, EventListener* pEventListener);
    //void RemoveListener(EventListener* pEventListener);

    void TriggerEvent(Event* pEvent);
};

#endif // !EVENTSYSTEM_H
