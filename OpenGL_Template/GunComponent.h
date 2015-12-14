//GunComponent.h

#ifndef GUNCOMPONENT_H
#define GUNCOMPONENT_H

#include "GameObjectComponent.h"

class SpawnManager;
class AudioComponent;

class GunComponent : public GameObjectComponent
{
private:
    SpawnManager* m_pSpawnManager;
    AudioComponent* m_pAudioComponent;

    float m_bulletSpeed;
    float m_bulletOffset;

    int m_shootCooldown;
    const int k_shootCooldownSet;
    bool m_gunCooled;

public:
    GunComponent(GameObject* pGameObject, TransformComponent* pTransform, SpawnManager* pSpawnManager, AudioComponent* pAudioComponent);

    virtual void Update() override;

    void Shoot();
    void Shoot(float angle);
    void Shoot(float unitVectorX, float unitVectorY);

private:
    void InternalShoot(float unitVectorX, float unitVectorY);
};

#endif // !GUNCOMPONENT_H