//ParticleComponent.h

#ifndef PARTICLECOMPONENT_H
#define PARTICLECOMPONENT_H

#include "GameObjectComponent.h"

class Rigidbody;

class ParticleComponent : public GameObjectComponent
{
private:
    int m_lifeTimerSet;
    int m_lifeTimer;

    Rigidbody* m_pRigidbody;

public:
    ParticleComponent(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody);
    ~ParticleComponent();

    virtual void Update() override;

    void Init();
};

#endif // !PARTICLECOMPONENT_H
