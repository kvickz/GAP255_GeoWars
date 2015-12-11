//Event.h

#ifndef EVENT_H
#define EVENT_H

#include "Constants.h"

class Event
{
private:
    static unsigned int s_eventInstanceCount;

    EventID m_eventID;
    EventInstanceID m_eventInstanceID;  //TODO: Implement?

public:
    Event(EventID eventID);
    virtual ~Event() {};

    const EventID& GetEventID() const { return m_eventID; }
};

//PLAYER DEATH EVENT
class PlayerDeathEvent : public Event
{
public:
    PlayerDeathEvent();
};

//PLAYER DEATH EVENT
class EnemyDeathEvent : public Event
{
public:
    EnemyDeathEvent();
};

#endif // !EVENT_H
