//Event.h

#ifndef EVENT_H
#define EVENT_H

#include "Constants.h"

#include "Vector3.h"

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
private:
    Vector3 m_location;
public:
    EnemyDeathEvent(Vector3 location);

    const Vector3 GetLocation() { return m_location; }
};

#endif // !EVENT_H
