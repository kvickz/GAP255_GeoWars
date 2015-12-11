//Rigidbody.h

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "GameObjectComponent.h"

#include "Vector2.h"
#include "Vector3.h"

class CollisionSystem;

class Rigidbody : public GameObjectComponent
{
private:
    CollisionSystem* m_pCollisionSystem;

    float m_mass;
    float m_dragFactor;
    Vector2_f m_velocity;

public:
    Rigidbody(GameObject* pGameObject, TransformComponent* pTransform, CollisionSystem* pCollisionSystem);
    ~Rigidbody();

    virtual void Update() override;

    void AddForce(float x, float y);
    void SetDrag(float value) { m_dragFactor = value; }
    void SetMass(float value) { m_mass = value; }

    Vector3 GetVelocity() const { return Vector3(m_velocity.x, 0, m_velocity.y); }
    float GetMass() const { return m_mass; }

private:
	void CheckForLevelBarrier();
	void BounceHorizontal();
	void BounceVertical();
	void AddDrag();
};

#endif // !RIGIDBODY_H
