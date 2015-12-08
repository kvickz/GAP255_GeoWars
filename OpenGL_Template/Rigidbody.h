//Rigidbody.h

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "GameObjectComponent.h"

#include "Vector2.h"

class Rigidbody : public GameObjectComponent
{
private:
    Vector2_f m_velocity;
    float m_maxSpeed;

public:
    Rigidbody(GameObject* pGameObject, TransformComponent* pTransform);

    virtual void Update() override;

    void AddForce(float x, float y);

private:
	void CheckForLevelBarrier();
	void BounceHorizontal();
	void BounceVertical();

	void ResetVelocity();
};

#endif // !RIGIDBODY_H
