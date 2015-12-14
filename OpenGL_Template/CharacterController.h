//CharacterController.h

#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "GameObjectComponent.h"

#include "Vector2.h"

class Rigidbody;
class AudioComponent;

class CharacterController : public GameObjectComponent
{
private:
    Vector2_f m_previousMoveVector;

    float m_moveSpeed;
    float m_maxSpeed;

    Rigidbody* m_pRigidbody;
    AudioComponent* m_pAudioComponent;

public:
    CharacterController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody, AudioComponent* pAudioComponent);
    ~CharacterController();

    //virtual void Init() override;
    virtual void Update() override;

    void Move(float x, float y);
    void Boost();

    void SetMaxSpeed(float value) { m_maxSpeed = value; }

private:

};

#endif // !CHARACTERCONTROLLER_H
