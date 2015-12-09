//CharacterController.h

#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "GameObjectComponent.h"

class Rigidbody;

class CharacterController : public GameObjectComponent
{
private:
    float m_moveSpeed;
    float m_maxSpeed;

    Rigidbody* m_pRigidbody;

public:
    CharacterController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody);
    ~CharacterController();

    virtual void Init() override;
    virtual void Update() override;

    void Move(float x, float y);

    void SetMaxSpeed(float value) { m_maxSpeed = value; }
};

#endif // !CHARACTERCONTROLLER_H
