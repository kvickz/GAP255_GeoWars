//GameObjectFactory.cpp

#include "GameObjectFactory.h"

#include "GameObjectComponentFactory.h"

GameObjectFactory::GameObjectFactory(Renderer* const pRenderer, Time* const pTime)
    :k_pRenderer(pRenderer)
    , k_pTime(pTime)
{
    //
}

//-------------------------------------------------------------------------------------- -
//  Create Planet Object
//-------------------------------------------------------------------------------------- -
GameObject* GameObjectFactory::CreatePlanet(Game* pGame)
{
    GameObjectComponentFactory componentFactory;
    GameObject* pObject = new GameObject(k_planetID, pGame);

    //Add Transform Component
    TransformComponent* pTransform = componentFactory.CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    //Add Render Component
    RenderComponent* pRenderComponent = componentFactory.CreateRenderComponent(pObject, pTransform);
    pObject->AddComponent(k_renderComponentID, pRenderComponent);

    return pObject;
}

//-------------------------------------------------------------------------------------- -
//  Create Camera Object
//-------------------------------------------------------------------------------------- -
GameObject* GameObjectFactory::CreateCamera(Game* pGame)
{
    GameObjectComponentFactory componentFactory;
    GameObject* pObject = new GameObject(k_cameraID, pGame);

    //Add Transform Component
    TransformComponent* pTransform = componentFactory.CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    //Add Camera Component
    CameraComponent* pCameraComponent = componentFactory.CreateCameraComponent(pObject, pTransform, k_pRenderer, k_pTime);
    pObject->AddComponent(k_cameraComponentID, pCameraComponent);

    return pObject;
}

//-------------------------------------------------------------------------------------- -
//  Create Player Object
//-------------------------------------------------------------------------------------- -
GameObject* GameObjectFactory::CreatePlayer(Game* pGame)
{
    GameObjectComponentFactory componentFactory;
    GameObject* pObject = new GameObject(k_characterControllerComponentID, pGame);

    //Add Transform Component
    TransformComponent* pTransform = componentFactory.CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    //Add Render Component
    RenderComponent* pRenderComponent = componentFactory.CreateRenderComponent(pObject, pTransform);
    pObject->AddComponent(k_renderComponentID, pRenderComponent);

    //Add Rigidbody
    Rigidbody* pRigidbody = componentFactory.CreateRigidbodyComponent(pObject, pTransform);
    pObject->AddComponent(pRigidbody->GetComponentID(), pRigidbody);

    //Add Character Controller Component
    CharacterController* pCharacterControllerComponent = componentFactory.CreateCharacterControllerComponent(pObject, pTransform, pRigidbody);
    pObject->AddComponent(k_characterControllerComponentID, pCharacterControllerComponent);

    return pObject;
}