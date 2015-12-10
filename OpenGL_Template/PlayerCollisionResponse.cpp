//PlayerCollisionResponse.cpp

#include "PlayerCollisionResponse.h"

#include "RenderComponent.h"
#include "Rigidbody.h"

PlayerCollisionResponse::PlayerCollisionResponse(Rigidbody* pRigidbody, CharacterController* pCharacterController, RenderComponent* pRenderComponent)
    :CollisionResponse(pRigidbody)
    , m_pCharacterController(pCharacterController)
    , m_pRenderComponent(pRenderComponent)
{
    //
}

void PlayerCollisionResponse::Execute(Vector3 force)
{
    m_pRigidbody->AddForce(force.x / 2, force.z / 2);

    m_pRenderComponent->SetColor(1.f, 1.f, 1.f);
}