//EventListener.h

#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "Constants.h"

class Event;
class EventSystem;

class EventListener
{
private:
    bool m_registered;

    EventSystem* m_pEventSystem;
    EventID m_eventID;

public:
    EventListener();
    virtual ~EventListener();

    virtual void OnEvent(Event* pEvent) = 0;
    void SetRegistrationActive(EventSystem* pEventSystem);

};

#endif // !EVENTLISTENER_H
