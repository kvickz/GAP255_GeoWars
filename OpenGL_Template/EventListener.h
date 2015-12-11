//EventListener.h

#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

class Event;

class EventListener
{
public:
    virtual ~EventListener() {}
    virtual void OnEvent(Event* pEvent) = 0;
};

#endif // !EVENTLISTENER_H
