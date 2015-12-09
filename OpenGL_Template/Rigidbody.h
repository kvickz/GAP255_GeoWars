//Rigidbody.h

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "GameObjectComponent.h"

#include "Vector2.h"
#include "Vector3.h"

class Rigidbody : public GameObjectComponent
{
private:
    float m_dragFactor;
    Vector2_f m_velocity;

public:
    Rigidbody(GameObject* pGameObject, TransformComponent* pTransform);

    virtual void Update() override;

    void AddForce(float x, float y);
    Vector3 GetVelocity() const { return Vector3(m_velocity.x, 0, m_velocity.y); }
    void SetDrag(float value) { m_dragFactor = value; }

private:
	void CheckForLevelBarrier();
	void BounceHorizontal();
	void BounceVertical();

	void AddDrag();
};

#endif // !RIGIDBODY_H
