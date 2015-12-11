//ParticleCollisionResponse.h

#ifndef PARTICLECOLLISIONRESPONSE_H
#define PARTICLECOLLISIONRESPONSE_H

#include "CollisionResponse.h"

class ParticleComponent;
class RenderComponent;

class ParticleCollisionResponse : public CollisionResponse
{
private:
    ParticleComponent* m_pParticleComponent;
    //RenderComponent* m_pRenderComponent;

public:
    ParticleCollisionResponse(Rigidbody* pRigidbody, ParticleComponent* pParticle);
    virtual void Execute(Collision collision);
};

#endif // !PARTICLECOLLISIONRESPONSE_H
