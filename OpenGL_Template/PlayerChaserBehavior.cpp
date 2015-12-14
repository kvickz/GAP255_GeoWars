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
    , k_findPlayerCounterSet(50)
    , m_findPlayerCounter(k_findPlayerCounterSet - 1)
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
        FindPlayer();
    }

    //Update move direction/speed
    m_pAIComponent->m_moveVector.x = m_pAIComponent->m_direction.x * m_moveSpeed;
    m_pAIComponent->m_moveVector.y = m_pAIComponent->m_direction.y * m_moveSpeed;
}

//-------------------------------------------------------------------------------------- -
//  Find Player Function
//      -This function iterates a counter every update which spaces out the number
//       of times to run a calculation to find the player.
//      -For example, if m_findPlayerCounterSet is equal to 100
//       that means that the game will only run the calculation to find the player
//       every 100 updates instead of every update for efficiency
//-------------------------------------------------------------------------------------- -
void PlayerChaserBehavior::FindPlayer()
{
    //Iterate the counter
    ++m_findPlayerCounter;

    if (m_findPlayerCounter >= k_findPlayerCounterSet)
    {
        //Run the calculation
        m_pAIComponent->FindPlayerDirection();

        //Reset the counter
        m_findPlayerCounter = 0;
    }
}