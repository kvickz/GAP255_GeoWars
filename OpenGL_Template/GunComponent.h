//GunComponent.h

#ifndef GUNCOMPONENT_H
#define GUNCOMPONENT_H

#include "GameObjectComponent.h"

class SpawnManager;

class GunComponent : public GameObjectComponent
{
private:
    SpawnManager* m_pSpawnManager;

    float m_bulletSpeed;
    float m_bulletOffset;

    int m_shootCooldown;
    const int k_shootCooldownSet;
    bool m_gunCooled;

public:
    GunComponent(GameObject* pGameObject, TransformComponent* pTransform, SpawnManager* pSpawnManager);

    virtual void Update() override;

    void Shoot();
};

#endif // !GUNCOMPONENT_H