//PlayerChaserBehavior.cpp

#include "PlayerChaserBehavior.h"

#include "EnemyAIComponent.h"
#include "TransformComponent.h"
#include "CharacterController.h"

//-------------------------------------------------------------------------------------- -
//  Constructor
//-------------------------------------------------------------------------------------- -
PlayerChaserBehavior::PlayerChaserBehavior(EnemyAIComponent* pAIComponent, float moveSpeed)
    :EnemyBehavior(pAIComponent)
    , m_moveSpeed(moveSpeed)
{
    //
}

//-------------------------------------------------------------------------------------- -
//  Destructor
//-------------------------------------------------------------------------------------- -
PlayerChaserBehavior::~PlayerChaserBehavior()
{
    //
}

//-------------------------------------------------------------------------------------- -
//  Player Chaser Execute
//      -Overrided function that chases the player every update
//-------------------------------------------------------------------------------------- -
void PlayerChaserBehavior::Execute()
{
    //Spinning
    m_pAIComponent->m_pTransform->Rotate(0, m_pAIComponent->rotateSpeed, 0);

    //Scaling
    //float scaleMag = 0.01f;
    //float scaleSpeed = 1.f;
    //scaleMag = sinf(SDL_GetTicks() * scaleSpeed) * scaleMag + scaleMag;
    //m_pTransform->Scale(scaleMag, 0, scaleMag);

    //Moving
    m_pAIComponent->m_pCharController->Move(m_pAIComponent->m_moveVector.x, m_pAIComponent->m_moveVector.y);

    //Find Player Direction
    if (m_pAIComponent->m_pTarget)
    {
        m_pAIComponent->FindPlayerDirection();
    }

    //Update move direction/speed
    m_pAIComponent->m_moveVector.x = m_pAIComponent->m_direction.x * m_moveSpeed;
    m_pAIComponent->m_moveVector.y = m_pAIComponent->m_direction.y * m_moveSpeed;
}