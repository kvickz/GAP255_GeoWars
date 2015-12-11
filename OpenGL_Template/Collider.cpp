//Collider.cpp

#include "Collider.h"

#include "TransformComponent.h"
#include "CollisionSystem.h"
#include "Rigidbody.h"

#include "CollisionResponse.h"

#include "Constants.h"
#include "Macros.h"

Collider::Collider(GameObject* pGameObject, TransformComponent* pTransform, CollisionSystem* pCollisionSystem, Rigidbody* pRigidbody)
    :GameObjectComponent(k_ColliderComponentID, pGameObject, pTransform)
    , m_pCollisionSystem(pCollisionSystem)
    , m_pCollisionResponse(nullptr)
    , m_collidedThisFrame(false)
    , m_pRigidbody(pRigidbody)
    , m_radius(2.f)
{
    pCollisionSystem->RegisterCollider(this);
}

Collider::~Collider()
{
    m_pCollisionSystem->RemoveCollider(this);

    SAFE_DELETE(m_pCollisionResponse);
}

void Collider::Update()
{
    m_collidedThisFrame = false;
}

bool Collider::CheckCollision(Collider* pOther)
{
    float touchingDistance = pOther->GetRadius();
    float distance = Vector3::Distance(GetPosition(), pOther->GetPosition());

    if (distance < touchingDistance)
        return true;    //Collision
    else
        return false;   //No Collision
}

void Collider::OnCollision(Collision collision)
{
    m_collidedThisFrame = true;

    if (m_pCollisionResponse)
        m_pCollisionResponse->Execute(collision);
}

Vector3 Collider::GetForce()
{
    return m_pRigidbody->GetVelocity();
}

float Collider::GetMass()
{
    return m_pRigidbody->GetMass();
}

Vector3 Collider::GetPosition()
{
    return m_pTransform->GetPosition();
}

//Specifies the type of response for collisions
void Collider::SetCollisionResponse(CollisionResponse* pCollisionResponse)
{
    m_pCollisionResponse = pCollisionResponse;
}