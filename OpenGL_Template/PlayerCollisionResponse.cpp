//PlayerCollisionResponse.cpp

#include "PlayerCollisionResponse.h"

#include "RenderComponent.h"
#include "Rigidbody.h"
#include "Collision.h"

#include "EventSystem.h"
#include "Event.h"

#include "Constants.h"

PlayerCollisionResponse::PlayerCollisionResponse(Rigidbody* pRigidbody, CharacterController* pCharacterController, RenderComponent* pRenderComponent)
    :CollisionResponse(pRigidbody)
    , m_pCharacterController(pCharacterController)
    , m_pRenderComponent(pRenderComponent)
{
    //
}

void PlayerCollisionResponse::Execute(Collision collision)
{
    

    switch (collision.m_objectID)
    {
    case k_enemy_1ID:
        m_pRenderComponent->SetColor(1.f, 1.f, 1.f);
        m_pRigidbody->AddForce(collision.m_force.x, collision.m_force.z);
        m_pRigidbody->GetEventSystem()->TriggerEvent(new PlayerDeathEvent());
        break;
    }
}