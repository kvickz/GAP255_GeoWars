//EnemyCollisionResponse.cpp

#include "EnemyCollisionResponse.h"

#include "EnemyAIComponent.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Collision.h"
#include "TransformComponent.h"

#include "EventSystem.h"
#include "Event.h"
#include "Game.h"

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
        KillEnemy();
        break;
    case k_bulletID:    //BULLET
        if (Game::GetGameMode() == GameMode::k_standard)
            KillEnemy();
        break;
    }
}

void EnemyCollisionResponse::KillEnemy()
{
    if (!m_enemyDied) 
    {
        m_pEnemyAIComponent->Kill(true);
        m_enemyDied = true;
    }
        
}