//CharacterController.h

#include "CharacterController.h"

#include "TransformComponent.h"
#include "Rigidbody.h"
#include "Constants.h"

CharacterController::CharacterController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody)
    :GameObjectComponent(k_characterControllerComponentID, pGameObject, pTransform)
    , m_pRigidbody(pRigidbody)
    , m_moveSpeed(0.1f)
    , m_maxSpeed(0.7f)
{
    //
}

CharacterController::~CharacterController()
{
    m_pGameObject = nullptr;
    m_pTransform = nullptr;
}

void CharacterController::Init()
{
    //
}

void CharacterController::Update()
{
    //
}

#include "Constants.h"
#include <cmath>

void CharacterController::Move(float x, float y)
{
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
	float angle = ((k_rad2Deg) * atan2f(y, x)) - (45.f);
	m_pTransform->SetEulerRotation(0, angle, 0);
}