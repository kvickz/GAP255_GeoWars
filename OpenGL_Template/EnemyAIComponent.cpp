//EnemyAIComponent.cpp

#include "EnemyAIComponent.h"

#include "PlayerChaserBehavior.h"
#include "EnemyFloaterBehavior.h"

#include "CharacterController.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include "Constants.h"
#include "Vector3.h"

#include <math.h>

//-------------------------------------------------------------------------------------- -
//  Constructor
//-------------------------------------------------------------------------------------- -
EnemyAIComponent::EnemyAIComponent(GameObject* pGameObject, TransformComponent* pTransform, CharacterController* pCharController, GameObject* pTarget)
    :GameObjectComponent(k_EnemyAIComponentID, pGameObject, pTransform)
    , m_pCharController(pCharController)
    , m_pTarget(pTarget)
    , m_pBehavior(nullptr)
    , m_behaviorType(EnemyBehaviorType::k_none)
    , m_moveSpeed(0.5f)
    , rotateSpeed(0.1f)
    , m_chasingPlayer(true)
{
    //Randomize the rotation direction
    int randVal = rand() % 2;

    if (randVal == 0)
        rotateSpeed *= -1;

    //Randomize the speed
    std::pair<float, float> m_possibleSpeeds(0.3f, 0.7f);

    m_moveSpeed = static_cast<float>(rand() / (static_cast<float>(RAND_MAX / (m_possibleSpeeds.second - m_possibleSpeeds.first))));
    //m_possibleSpeeds.first = 0.3f;
    //m_possibleSpeeds.second = 0.7f;

    //SetBehavior(EnemyBehaviorType::k_chaser);
}

//-------------------------------------------------------------------------------------- -
//  Destructor
//-------------------------------------------------------------------------------------- -
EnemyAIComponent::~EnemyAIComponent()
{
    delete m_pBehavior;
    m_pBehavior = nullptr;
}

void EnemyAIComponent::Update()
{
    if (m_pBehavior)
        m_pBehavior->Execute();
}

//-------------------------------------------------------------------------------------- -
//  Find Player Direction Function
//      -Gets the unit vector in the direction of the player
//       then multiplies by it's speed
//-------------------------------------------------------------------------------------- -
void EnemyAIComponent::FindPlayerDirection()
{
	//Get Unit Vector on x and z planes
	Vector3 targetPos = m_pTarget->GetTransformComponent()->GetPosition();
	Vector3 myPos = m_pTransform->GetPosition();

	float xDistance = (targetPos.x - myPos.x);
	float yDistance = -(targetPos.z - myPos.z);

	float xDistSquared = xDistance * xDistance;
	float yDistSquared = yDistance * yDistance;

	float magnitude = xDistSquared + yDistSquared;

    //TODO: Optimize this
	magnitude = sqrt(magnitude);

	m_direction.x = xDistance / magnitude;
	m_direction.y = yDistance / magnitude;
}

//-------------------------------------------------------------------------------------- -
//  Set Behavior Function
//      -Helper function to assign a behavior to an enemy
//-------------------------------------------------------------------------------------- -
void EnemyAIComponent::SetBehavior(EnemyBehaviorType type)
{
    if (m_behaviorType == type)
        return;

    delete m_pBehavior;

    switch (type)
    {
    case EnemyBehaviorType::k_chaser:
        m_pBehavior = new PlayerChaserBehavior(this, m_moveSpeed);
        break;
    case EnemyBehaviorType::k_floater:
        m_pBehavior = new EnemyFloaterBehavior(this, 0.7f);
        break;
    case EnemyBehaviorType::k_none:
        m_pBehavior = nullptr;
        break;
    }

    m_behaviorType = type;
}