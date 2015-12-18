//EnemyAIComponent.cpp

#include "EnemyAIComponent.h"

#include "PlayerChaserBehavior.h"
#include "EnemyFloaterBehavior.h"

#include "CharacterController.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include "Time.h"
#include "EventSystem.h"
#include "Event.h"

#include "Constants.h"
#include "Vector3.h"
#include "Macros.h"

#include <math.h>

//-------------------------------------------------------------------------------------- -
//  Constructor
//-------------------------------------------------------------------------------------- -
EnemyAIComponent::EnemyAIComponent(GameObject* pGameObject, TransformComponent* pTransform, CharacterController* pCharController, GameObject* pTarget, AudioComponent* pAudioComponent, SpawnManager* pSpawnManager)
    :GameObjectComponent(k_enemyAIComponentID, pGameObject, pTransform)
    , m_pCharController(pCharController)
    , m_pAudioComponent(pAudioComponent)
    , m_pSpawnManager(pSpawnManager)
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

    RegisterForEvents();
}

//-------------------------------------------------------------------------------------- -
//  Destructor
//-------------------------------------------------------------------------------------- -
EnemyAIComponent::~EnemyAIComponent()
{
    m_pGameObject->GetEventSystem()->RemoveListener(k_playerDeathEvent, this);

    SAFE_DELETE(m_pBehavior);
}

//-------------------------------------------------------------------------------------- -
//  Update
//-------------------------------------------------------------------------------------- -
void EnemyAIComponent::Update()
{
    if (m_markedForDeath)
    {
        m_timeTilDeath -= Time::GetDeltaTime();

        if (m_timeTilDeath <= 0)
            Kill(false);

        return;
    }

    if (m_pBehavior)
        m_pBehavior->Execute();
}

//-------------------------------------------------------------------------------------- -
//  On Event Function
//-------------------------------------------------------------------------------------- -

void EnemyAIComponent::OnEvent(Event* pEvent)
{
    //When player dies, all enemies die
    switch (pEvent->GetEventID())
    {
    case k_playerDeathEvent:
        //Kill(false);
        MarkForDeath();
        break;
    }
}

void EnemyAIComponent::RegisterForEvents()
{
    m_pGameObject->GetEventSystem()->RegisterListener(k_playerDeathEvent, this);
}

#include "AudioComponent.h"
#include "AudioFileEnums.h"
#include "SpawnManager.h"

void EnemyAIComponent::Kill(bool withParticles)
{
    GetEventSystem()->TriggerEvent(new EnemyDeathEvent(GetTransform()->GetPosition()));

    if (withParticles)
        m_pSpawnManager->SpawnDeathParticles(GetTransform()->GetPosition());

    m_pAudioComponent->PlaySound(SFX::k_enemyDeath_SFX);
    GetGameObject()->DeleteObject();
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

//-------------------------------------------------------------------------------------- -
//  Set Behavior Function
//      -Assigns the enemy a random timer until they die
//-------------------------------------------------------------------------------------- -
void EnemyAIComponent::MarkForDeath()
{
    const int max_possibleValue = 1100;
    const int min_possibleValue = 110;

    m_timeTilDeath = rand() % (max_possibleValue - min_possibleValue) + min_possibleValue;

    m_markedForDeath = true;
    
}