//CharacterController.h

#include "CharacterController.h"

#include "TransformComponent.h"
#include "Rigidbody.h"
#include "Constants.h"

#include <cmath>

CharacterController::CharacterController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody, AudioComponent* pAudioComponent)
    :GameObjectComponent(k_characterControllerComponentID, pGameObject, pTransform)
    , m_pRigidbody(pRigidbody)
    , m_pAudioComponent(pAudioComponent)
    , m_moveSpeed(0.1f)
    , m_maxSpeed(0.7f)
{
    //
}

CharacterController::~CharacterController()
{
    m_pGameObject = nullptr;
    m_pTransform = nullptr;
    m_pAudioComponent = nullptr;
}

//void CharacterController::Init() { }

void CharacterController::Update()
{
    //
}

void CharacterController::Move(float x, float y)
{
    //Storing value for boost
    m_previousMoveVector.x = x;
    m_previousMoveVector.y = y;

    float xVal = x * m_moveSpeed;
    float yVal = y * -m_moveSpeed;

    Vector3 rigidbodyVelocity = m_pRigidbody->GetVelocity();

    //Limiting the acceleration speed
    if ((rigidbodyVelocity.x > m_maxSpeed) || (rigidbodyVelocity.x < -m_maxSpeed))
        xVal = 0;

    if ((rigidbodyVelocity.z > m_maxSpeed) || (rigidbodyVelocity.z < -m_maxSpeed))
        yVal = 0;

    m_pRigidbody->AddForce(xVal, yVal);

	//Set rotation
	float angle = ((k_rad2Deg) * atan2f(y, x)) + (90.f);
	m_pTransform->SetEulerRotation(0, angle, 0);
}

void CharacterController::Boost()
{
    m_pRigidbody->AddForce(m_previousMoveVector.x, -m_previousMoveVector.y);
}