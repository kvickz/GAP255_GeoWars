//BulletController.cpp

#include "BulletController.h"

#include "GameObject.h"
#include "Rigidbody.h"
#include "Time.h"

#include "Constants.h"

BulletController::BulletController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody)
    :GameObjectComponent(k_bulletComponentID, pGameObject, pTransform)
    , m_pRigidbody(pRigidbody)
    , k_lifeTimeSet(1000)
{
    m_lifeTime = k_lifeTimeSet;
    m_bulletVelocity = Vector3(2, 0, 0);
    m_pRigidbody->SetDrag(0.99f);
}

void BulletController::Update()
{
    m_lifeTime -= Time::GetDeltaTime();

    if (m_lifeTime < 0)
    {
        DestroyBullet();
    }
}

void BulletController::Init(Vector3 bulletVelocity)
{
    m_bulletVelocity = bulletVelocity;

    m_pRigidbody->AddForce(bulletVelocity.x, bulletVelocity.z);
}

void BulletController::DestroyBullet()
{
    m_pRigidbody->GetGameObject()->DeleteObject();
    //Spawn Particles
}