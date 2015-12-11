//ParticleComponent.cpp

#include "ParticleComponent.h"

#include "GameObject.h"
#include "Rigidbody.h"
#include "Time.h"

ParticleComponent::ParticleComponent(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody)
    :GameObjectComponent(k_ParticleComponentID, pGameObject, pTransform)
    , m_pRigidbody(pRigidbody)
{
    m_lifeTimerSet = rand() % 500;
    m_lifeTimer = m_lifeTimerSet;

    m_pRigidbody->SetDrag(0.95f);

    int k_amplitude = (rand() % 7) + 3;
    float randX = (float)(rand() % k_amplitude) - k_amplitude / 2;
    float randY = (float)(rand() % k_amplitude) - k_amplitude / 2;
    m_pRigidbody->AddForce(randX, randY);
}

ParticleComponent::~ParticleComponent()
{
    //
}

void ParticleComponent::Update()
{
    m_lifeTimer -= Time::GetDeltaTime();

    if (m_lifeTimer <= 0)
    {
        m_pGameObject->DeleteObject();
    }
}

void ParticleComponent::Init()
{
    //
}
