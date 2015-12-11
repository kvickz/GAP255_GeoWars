//GunComponent.cpp

#include "GunComponent.h"

#include "TransformComponent.h"
#include "BulletController.h"
#include "SpawnManager.h"
#include "GameObject.h"
#include "Time.h"

#include "Constants.h"

#include <math.h>

GunComponent::GunComponent(GameObject* pGameObject, TransformComponent* pTransform, SpawnManager* pSpawnManager)
    :GameObjectComponent(k_gunComponentID, pGameObject, pTransform)
    , m_pSpawnManager(pSpawnManager)
    , m_bulletSpeed(2.f)
    , m_bulletOffset(5.f)
    , k_shootCooldownSet(250)
    , m_shootCooldown(k_shootCooldownSet)
    , m_gunCooled(true)
{
    //
}

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

void GunComponent::Shoot()
{
    if (!m_gunCooled)
        return;

    //
    float angle = (-m_pTransform->GetRotation().y + 90) * k_deg2Rad;
    float xUnit = cosf(angle);
    float yUnit = sinf(angle);
    float xVel = xUnit * m_bulletSpeed;
    float yVel = yUnit * m_bulletSpeed;
    float xPos = xUnit * m_bulletOffset;
    float yPos = yUnit * m_bulletOffset;

    //Offset the bullet's position from the player's position
    Vector3 position = Vector3(m_pTransform->GetPosition());
    position.x += xPos;
    position.z += yPos;

    GameObject* pObject = m_pSpawnManager->SpawnBullet(position);
    BulletController* pBulletController = pObject->GetComponent<BulletController>(k_bulletComponentID);

    //Determine the angle
    Vector3 bulletVelocity(xVel, 0, yVel);
    pBulletController->Init(bulletVelocity);

    //Spawn Bullet
    m_shootCooldown = k_shootCooldownSet;
    m_gunCooled = false;
}