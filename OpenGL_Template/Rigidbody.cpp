//Rigidbody.cpp

#include "Rigidbody.h"

#include "TransformComponent.h"
#include "Constants.h"

Rigidbody::Rigidbody(GameObject* pGameObject, TransformComponent* pTransform)
    :GameObjectComponent(k_rigidbodyComponentID, pGameObject, pTransform)
    , m_maxSpeed(1)
{
    //
}

void Rigidbody::Update()
{
    //Update Velocity
    m_pTransform->Translate(m_velocity.x, 0, m_velocity.y);
}

void Rigidbody::AddForce(float x, float y)
{
    m_velocity.x += x;
    m_velocity.y += y;

    if (m_velocity.x > m_maxSpeed)
        m_velocity.x = m_maxSpeed;

    if (m_velocity.x < -m_maxSpeed)
        m_velocity.x = -m_maxSpeed;

    if (m_velocity.y > m_maxSpeed)
        m_velocity.y = m_maxSpeed;

    if (m_velocity.y < -m_maxSpeed)
        m_velocity.y = -m_maxSpeed;
}