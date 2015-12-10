//CollisionSystem.h

#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <vector>

#include "Vector3.h"

class Rigidbody;
class Collider;

class CollisionSystem
{
private:
    std::vector<Rigidbody*> m_rigidbodies;
    std::vector<Collider*> m_colliders;
	//TODO: Rigidbodies register themselves with this system

public:
    CollisionSystem();
    ~CollisionSystem();

    void RegisterRigidbody(Rigidbody* pRigidbody);
    void RemoveRigidbody(Rigidbody* pRigidbody);

    void RegisterCollider(Collider* pCollider);
    void RemoveCollider(Collider* pCollider);

    void Update();

private:
    void CheckForCollisions();
    void CalculateCollisionForces(Vector3& a, Vector3& b);
};

#endif // !COLLISIONSYSTEM_H
