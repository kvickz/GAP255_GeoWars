//EnemyFloaterBehavior.cpp

#include "EnemyFloaterBehavior.h"

#include "EnemyAIComponent.h"
#include "CharacterController.h"
#include "Rigidbody.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include "Constants.h"

EnemyFloaterBehavior::EnemyFloaterBehavior(EnemyAIComponent* pAIComponent, float moveSpeed)
    :EnemyBehavior(pAIComponent)
    , m_moveSpeed(moveSpeed)
{
    m_pAIComponent->GetGameObject()->GetComponent<Rigidbody>(k_rigidbodyComponentID)->SetDrag(1.0f);

    //Update move direction/speed
    m_pAIComponent->m_moveVector.x = m_moveSpeed;
    m_pAIComponent->m_moveVector.y = m_moveSpeed;

    //Moving
    m_pAIComponent->m_pCharController->Move(m_pAIComponent->m_moveVector.x, m_pAIComponent->m_moveVector.y);
}

EnemyFloaterBehavior::~EnemyFloaterBehavior()
{
    //
}

void EnemyFloaterBehavior::Execute()
{
    //Spinning
    m_pAIComponent->m_pTransform->Rotate(0, m_pAIComponent->m_moveVector.x, 0);

}