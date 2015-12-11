//EnemyCollisionResponse.cpp

#include "EnemyCollisionResponse.h"

#include "EnemyAIComponent.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Collision.h"
#include "TransformComponent.h"

#include "EventSystem.h"
#include "Event.h"

#include "Constants.h"

EnemyCollisionResponse::EnemyCollisionResponse(Rigidbody* pRigidbody, EnemyAIComponent* pEnemyAIComponent)
    :CollisionResponse(pRigidbody)
    , m_pEnemyAIComponent(pEnemyAIComponent)
{
    //
}

void EnemyCollisionResponse::Execute(Collision collision)
{
    //force = force * 1.1f;
    m_pRigidbody->AddForce(collision.m_force.x, collision.m_force.z);

    switch (collision.m_objectID)
    {
    case k_playerID:    //PLAYER
        m_pEnemyAIComponent->Kill();
        break;
    case k_bulletID:    //BULLET
        m_pEnemyAIComponent->Kill();
        //KillEnemy();
        break;
    }
}

void EnemyCollisionResponse::KillEnemy()
{
    Vector3 location = m_pRigidbody->GetTransform()->GetPosition();
    m_pRigidbody->GetEventSystem()->TriggerEvent(new EnemyDeathEvent(location));
    m_pRigidbody->GetGameObject()->DeleteObject();
}