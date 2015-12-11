//BulletController.h

#ifndef BULLETCONTROLLER_H
#define BULLETCONTROLLER_H

#include "GameObjectComponent.h"

#include "Vector3.h"

class Rigidbody;

class BulletController : public GameObjectComponent
{
private:
    Vector3 m_bulletVelocity;

    Rigidbody* m_pRigidbody;

    int m_lifeTime;
    const int k_lifeTimeSet;

public:
    BulletController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody);

    virtual void Update() override;

    void Init(Vector3 bulletVelocity);

private:
    void DestroyBullet();
};

#endif // !BULLETCONTROLLER_H
