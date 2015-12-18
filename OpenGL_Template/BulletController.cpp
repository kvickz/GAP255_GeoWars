//BulletController.cpp

#include "BulletController.h"

#include "GameObject.h"
#include "Rigidbody.h"
#include "AudioComponent.h"
#include "Time.h"

#include "Constants.h"
#include "AudioFileEnums.h"

BulletController::BulletController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody, AudioComponent* pAudioComponent)
    :GameObjectComponent(k_bulletComponentID, pGameObject, pTransform)
    , m_pAudioComponent(pAudioComponent)
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
    if (!m_bulletAlive)
        return;
    
    m_pAudioComponent->PlaySound(SFX::k_bulletDeath_SFX);
    m_pRigidbody->GetGameObject()->DeleteObject();
    m_bulletAlive = false;
}