//GameObjectComponentFactory.cpp

#include "GameObjectComponentFactory.h"

//TRANSFORM COMPONENT
TransformComponent* GameObjectComponentFactory::CreateTransformComponent(GameObject* pGameObject)
{
    TransformComponent* pComponent = new TransformComponent(k_transformComponentID, pGameObject);

    return pComponent;
}

//RENDER COMPONENT
RenderComponent* GameObjectComponentFactory::CreateRenderComponent(GameObject* pGameObject, TransformComponent* pTransform)
{
    RenderComponent* pComponent = new RenderComponent(k_renderComponentID, pGameObject, pTransform);

    return pComponent;
}

//CAMERA COMPONENT
CameraComponent* GameObjectComponentFactory::CreateCameraComponent(GameObject* pGameObject, TransformComponent* pTransform, Renderer* const pRenderer, Time* const pTime)
{
    CameraComponent* pComponent = new CameraComponent(k_cameraComponentID, pGameObject, pTransform, pRenderer, pTime);

    return pComponent;
}

//RIGIDBODY
Rigidbody* GameObjectComponentFactory::CreateRigidbodyComponent(GameObject* pGameObject, TransformComponent* pTransform, CollisionSystem* pCollisionSystem)
{
    Rigidbody* pComponent = new Rigidbody(pGameObject, pTransform, pCollisionSystem);

    return pComponent;
}

//CHARACTER CONTROLLER
CharacterController* GameObjectComponentFactory::CreateCharacterControllerComponent(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody)
{
    CharacterController* pComponent = new CharacterController(pGameObject, pTransform, pRigidbody);

    return pComponent;
}

//AI CONTROLLER
EnemyAIComponent* GameObjectComponentFactory::CreateEnemyAIComponent(GameObject* pGameObject, TransformComponent* pTransform, CharacterController* pCharController, GameObject* pTarget)
{
	EnemyAIComponent* pComponent = new EnemyAIComponent(pGameObject, pTransform, pCharController, pTarget);

	return pComponent;
}

//COLLIDER
Collider* GameObjectComponentFactory::CreateCollider(GameObject* pGameObject, TransformComponent* pTransform, CollisionSystem* pCollisionSystem, Rigidbody* pRigidbody)
{
    Collider* pComponent = new Collider(pGameObject, pTransform, pCollisionSystem, pRigidbody);

    return pComponent;
}

//CHARACTER STATS
CharacterStats* GameObjectComponentFactory::CreateCharacterStats(GameObject* pGameObject, TransformComponent* pTransform)
{
    CharacterStats* pComponent = new CharacterStats(pGameObject, pTransform);

    return pComponent;
}

//***************************
//  FUNCTION TEMPLATE
//***************************
/*
//
* GameObjectComponentFactory::Create(GameObject* pGameObject, TransformComponent* pTransform)
{
    * pComponent = new (pGameObject, pTransform);

    return pComponent;
}
*/