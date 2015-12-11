//Collider.h

#ifndef COLLIDER_H
#define COLLIDER_H

#include "GameObjectComponent.h"

#include "Vector3.h"
#include "Collision.h"

#include "Constants.h"

class CollisionSystem;
class CollisionResponse;
class Rigidbody;

class Collider : public GameObjectComponent
{
private:
    CollisionSystem* m_pCollisionSystem;
    CollisionResponse* m_pCollisionResponse;
    Rigidbody* m_pRigidbody;
    float m_radius;

    bool m_collidedThisFrame;

public:
    Collider(GameObject* pGameObject, TransformComponent* pTransform, CollisionSystem* pCollisionSystem, Rigidbody* pRigidbody);
    ~Collider();

    virtual void Update() override;

    bool CheckCollision(Collider* pOther);
    void SetRadius(float value) { m_radius = value; }
    void SetCollisionResponse(CollisionResponse* pCollisionResponse);
    bool HasCollidedThisFrame() { return m_collidedThisFrame; }
    void OnCollision(Collision collision);
    
    Vector3 GetForce();
    float GetMass();
private:
    float GetRadius() { return m_radius; }
    Vector3 GetPosition();
};

#endif // !COLLIDER_H




