//EnemyCollisionResponse.cpp

#include "EnemyCollisionResponse.h"

#include "Rigidbody.h"

EnemyCollisionResponse::EnemyCollisionResponse(Rigidbody* pRigidbody, EnemyAIComponent* pEnemyAIComponent)
    :CollisionResponse(pRigidbody)
    , m_pEnemyAIComponent(pEnemyAIComponent)
{
    //
}

void EnemyCollisionResponse::Execute(Vector3 force)
{
    force = force * 1.1f;
    m_pRigidbody->AddForce(force.x, force.z);
}