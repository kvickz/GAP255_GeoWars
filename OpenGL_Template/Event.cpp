//Event.cpp

#include "Event.h"

unsigned int Event::s_eventInstanceCount = 0;

//***************************************************************************************
//  BASE EVENT CLASS
//***************************************************************************************
Event::Event(EventID eventID)
    :m_eventID(eventID)
{
    ++s_eventInstanceCount;
}

//***************************************************************************************
//  PLAYER DEATH EVENT
//***************************************************************************************
PlayerDeathEvent::PlayerDeathEvent()
    :Event(k_playerDeathEvent)
{

}

//***************************************************************************************
//  ENEMY DEATH EVENT
//***************************************************************************************
EnemyDeathEvent::EnemyDeathEvent()
    :Event(k_enemyDeathEvent)
{

}
