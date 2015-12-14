//GunComponent.cpp

#include "GunComponent.h"

#include "TransformComponent.h"
#include "BulletController.h"
#include "AudioComponent.h"
#include "SpawnManager.h"
#include "GameObject.h"
#include "Time.h"

#include "Constants.h"
#include "AudioFileEnums.h"

#include <math.h>

//-------------------------------------------------------------------------------------- -
//  Gun Component Constructor
//-------------------------------------------------------------------------------------- -
GunComponent::GunComponent(GameObject* pGameObject, TransformComponent* pTransform, SpawnManager* pSpawnManager, AudioComponent* pAudioComponent)
    :GameObjectComponent(k_gunComponentID, pGameObject, pTransform)
    , m_pSpawnManager(pSpawnManager)
    , m_pAudioComponent(pAudioComponent)
    , m_bulletSpeed(2.f)
    , m_bulletOffset(10.f)
    , k_shootCooldownSet(250)
    , m_shootCooldown(k_shootCooldownSet)
    , m_gunCooled(true)
{
    //
}

//-------------------------------------------------------------------------------------- -
//  Update Function
//-------------------------------------------------------------------------------------- -
void GunComponent::Update()
{
    if (m_shootCooldown > 0)
    {
        m_shootCooldown -= Time::GetDeltaTime();
    }
    else
    {
        m_gunCooled = true;
    }
        
}

//-------------------------------------------------------------------------------------- -
//  Shoot Function
//      -Will shoot in the direction of player movement
//-------------------------------------------------------------------------------------- -
void GunComponent::Shoot()
{
    float angle = (-m_pTransform->GetRotation().y + 90) * k_deg2Rad;
    
    Shoot(angle);
}

//-------------------------------------------------------------------------------------- -
//  Shoot Function
//      -Will shoot in the direction of angle
//-------------------------------------------------------------------------------------- -
void GunComponent::Shoot(float angle)
{
    if (!m_gunCooled)
        return;

    float xUnit = cosf(angle);
    float yUnit = sinf(angle);

    InternalShoot(xUnit, yUnit);
}

void GunComponent::Shoot(float unitVectorX, float unitVectorY)
{
    if (!m_gunCooled)
        return;

    InternalShoot(unitVectorX, unitVectorY);
}

//-------------------------------------------------------------------------------------- -
//  Shoot Function
//      -Processes logic necessary for shooting
//-------------------------------------------------------------------------------------- -
void GunComponent::InternalShoot(float unitVectorX, float unitVectorY)
{
    float xVel = unitVectorX * m_bulletSpeed;
    float yVel = unitVectorY * m_bulletSpeed;
    float xPos = unitVectorX * m_bulletOffset;
    float yPos = unitVectorY * m_bulletOffset;

    //Offset the bullet's position from the player's position
    Vector3 position = Vector3(m_pTransform->GetPosition());
    position.x += xPos;
    position.z += yPos;

    //Spawn Bullet
    GameObject* pObject = m_pSpawnManager->SpawnBullet(position);
    BulletController* pBulletController = pObject->GetComponent<BulletController>(k_bulletComponentID);

    //Determine the angle
    Vector3 bulletVelocity(xVel, 0, yVel);
    pBulletController->Init(bulletVelocity);

    //Play Audio
    m_pAudioComponent->PlaySound(k_shoot_01_SFX);

    m_shootCooldown = k_shootCooldownSet;
    m_gunCooled = false;
}