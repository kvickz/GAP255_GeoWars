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
Rigidbody* GameObjectComponentFactory::CreateRigidbodyComponent(GameObject* pGameObject, TransformComponent* pTransform)
{
    Rigidbody* pComponent = new Rigidbody(pGameObject, pTransform);

    return pComponent;
}

//CHARACTER CONTROLLER
CharacterController* GameObjectComponentFactory::CreateCharacterControllerComponent(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody)
{
    CharacterController* pComponent = new CharacterController(pGameObject, pTransform, pRigidbody);

    return pComponent;
}