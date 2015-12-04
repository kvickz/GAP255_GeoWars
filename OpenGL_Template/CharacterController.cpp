//CharacterController.h

#include "CharacterController.h"

#include "TransformComponent.h"
#include "Rigidbody.h"
#include "Constants.h"

CharacterController::CharacterController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody)
    :GameObjectComponent(k_characterControllerComponentID, pGameObject, pTransform)
    , m_pRigidbody(pRigidbody)
    , m_moveSpeed(0.1f)
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

void CharacterController::Move(float x, float y)
{
    float xVal = x * m_moveSpeed;
    float yVal = y * m_moveSpeed;

    m_pRigidbody->AddForce(xVal, yVal);
}