//CollisionSystem.cpp

#include "CollisionSystem.h"

#include "Rigidbody.h"
#include "TransformComponent.h"
#include "Collider.h"
#include "Collision.h"

//-------------------------------------------------------------------------------------- -
//  Constructor
//-------------------------------------------------------------------------------------- -
CollisionSystem::CollisionSystem()
{
    //
}

//-------------------------------------------------------------------------------------- -
//  Destructor
//-------------------------------------------------------------------------------------- -
CollisionSystem::~CollisionSystem()
{
    //Safety check, cleanup any leftover rigidbodies
    auto iterator = m_rigidbodies.begin();
    while (iterator != m_rigidbodies.end())
    {
        delete (*iterator);
        ++iterator;
    }
}

//-------------------------------------------------------------------------------------- -
//  Update Function
//-------------------------------------------------------------------------------------- -
void CollisionSystem::Update()
{
    CheckForCollisions();
}

void CollisionSystem::CheckForCollisions()
{
    //n^2 algorithm
    for (unsigned int i = 0; i < m_colliders.size(); ++i)
    {
        for (unsigned int j = 0; j < m_colliders.size(); ++j)
        {
            //Dont check an object colliding with itself
            if (i == j)
                continue;

            //if !collided
            if (!m_colliders[i]->CheckCollision(m_colliders[j]))
                continue;

            //if either object has already collided this frame, ignore it
            if (m_colliders[i]->HasCollidedThisFrame() || m_colliders[j]->HasCollidedThisFrame())
                continue;
            
            //Get the forces
            Vector3 forceA = m_colliders[i]->GetForce() * m_colliders[i]->GetMass();
            Vector3 forceB = m_colliders[j]->GetForce() * m_colliders[j]->GetMass();

            //Calculate the result
            CalculateCollisionForces(forceA, forceB);

            //Create Collision Objects
            Collision collisionA(forceB, m_colliders[j]->GetTransform()->GetPosition(), m_colliders[j]->GetGameObjectID());
            Collision collisionB(forceA, m_colliders[i]->GetTransform()->GetPosition(), m_colliders[i]->GetGameObjectID());

            //Execute collision behavior
            m_colliders[i]->OnCollision(collisionA);
            m_colliders[j]->OnCollision(collisionB);
        }
    }
}

void CollisionSystem::CalculateCollisionForces(Vector3& a, Vector3& b)
{
    //Get the relative force, equal and opposite
    Vector3 relativeForceA = a - b;
    Vector3 relativeForceB = relativeForceA * -1;

    //The force applied is an even distribution between the forces
    Vector3 resultantForceA = a + relativeForceA / 2;
    Vector3 resultantForceB = b + relativeForceB / 2;

    a = relativeForceA;
    b = relativeForceB;
}

void CollisionSystem::RegisterRigidbody(Rigidbody* pRigidbody)
{
    m_rigidbodies.push_back(pRigidbody);
}

void CollisionSystem::RemoveRigidbody(Rigidbody* pRigidbody)
{
    auto findIt = std::find(m_rigidbodies.begin(), m_rigidbodies.end(), pRigidbody);

    if (*findIt)
    {
        m_rigidbodies.erase(findIt);
    }
}

void CollisionSystem::RegisterCollider(Collider* pCollider)
{
    m_colliders.push_back(pCollider);
}

void CollisionSystem::RemoveCollider(Collider* pCollider)
{
    auto findIt = std::find(m_colliders.begin(), m_colliders.end(), pCollider);

    if (*findIt)
    {
        m_colliders.erase(findIt);
    }
}