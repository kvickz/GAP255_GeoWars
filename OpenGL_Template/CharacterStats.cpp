//CharacterStats.cpp

#include "CharacterStats.h"

#include "Constants.h"

CharacterStats::CharacterStats(GameObject* pGameObject, TransformComponent* pTransform)
    :GameObjectComponent(k_CharacterStatsComponentID, pGameObject, pTransform)
{
    //
}

CharacterStats::~CharacterStats()
{
    //
}

void CharacterStats::Damage(unsigned int amount)
{
    m_HP -= amount;

    if (m_HP < 0)
    {
        //Trigger Character Death Event
        //EventSystem->Trigger
    }
}

void CharacterStats::Heal(unsigned int amount)
{
    //
}
