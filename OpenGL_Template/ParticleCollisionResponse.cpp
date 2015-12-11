//ParticleCollisionResponse.cpp

#include "ParticleCollisionResponse.h"

#include "Collision.h"
#include "Rigidbody.h"

ParticleCollisionResponse::ParticleCollisionResponse(Rigidbody* pRigidbody, ParticleComponent* pParticle)
    :CollisionResponse(pRigidbody)
{
    //
}

void ParticleCollisionResponse::Execute(Collision collision)
{
    collision.m_force = collision.m_force;

    m_pRigidbody->AddForce(collision.m_force.x, collision.m_force.z);

}