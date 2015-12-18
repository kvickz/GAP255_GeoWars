//BulletController.h

#ifndef BULLETCONTROLLER_H
#define BULLETCONTROLLER_H

#include "GameObjectComponent.h"

#include "Vector3.h"

class Rigidbody;
class AudioComponent;

class BulletController : public GameObjectComponent
{
private:
    bool m_bulletAlive = true;
    Vector3 m_bulletVelocity;

    Rigidbody* m_pRigidbody;
    AudioComponent* m_pAudioComponent;

    int m_lifeTime;
    const int k_lifeTimeSet;

public:
    BulletController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody, AudioComponent* pAudioComponent);

    virtual void Update() override;

    void Init(Vector3 bulletVelocity);
    void DestroyBullet();

};

#endif // !BULLETCONTROLLER_H
