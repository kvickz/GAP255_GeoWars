//CharacterController.h

#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "GameObjectComponent.h"

class Rigidbody;

class CharacterController : public GameObjectComponent
{
private:
    float m_moveSpeed;

    Rigidbody* m_pRigidbody;

public:
    CharacterController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody);
    ~CharacterController();

    virtual void Init() override;
    virtual void Update() override;

    void Move(float x, float y);
};

#endif // !CHARACTERCONTROLLER_H
