//ParticleComponent.h

#ifndef PARTICLECOMPONENT_H
#define PARTICLECOMPONENT_H

#include "GameObjectComponent.h"

class ParticleComponent : public GameObjectComponent
{
private:
    int m_lifeTimerSet;
    int m_lifeTimer;

public:
    ParticleComponent(GameObject* pGameObject, TransformComponent* pTransform, int lifeTime);
    ~ParticleComponent();
};

#endif // !PARTICLECOMPONENT_H
