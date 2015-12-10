//CharacterStats.h

#ifndef CHARACTERSTATS_H
#define CHARACTERSTATS_H

#include "GameObjectComponent.h"

class CharacterStats : public GameObjectComponent
{
    unsigned int m_HP;

public:
    CharacterStats(GameObject* pGameObject, TransformComponent* pTransform);
    ~CharacterStats();

    void Damage(unsigned int amount);
    void Heal(unsigned int amount);
};

#endif // !CHARACTERSTATS_H
