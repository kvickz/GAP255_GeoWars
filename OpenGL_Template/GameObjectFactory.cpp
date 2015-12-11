//GameObjectFactory.cpp

#include "GameObjectFactory.h"

#include "GameObjectComponentFactory.h"

#include "PlayerCollisionResponse.h"
#include "EnemyCollisionResponse.h"

GameObjectFactory::GameObjectFactory(Renderer* const pRenderer, Time* const pTime, CollisionSystem* const pCollisionSystem, AssetManager* const pAssetManager)
    :k_pRenderer(pRenderer)
    , k_pAssetManager(pAssetManager)
    , k_pCollisionSystem(pCollisionSystem)
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
//  Create Procedural Wall
//-------------------------------------------------------------------------------------- -
GameObject* GameObjectFactory::CreateWall(Game* pGame, std::vector<float> vertices, std::vector<unsigned int> indices)
{
    GameObjectComponentFactory componentFactory;
    GameObject* pObject = new GameObject(k_wallID, pGame);

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
    GameObject* pObject = new GameObject(k_playerID, pGame);

    //Add Transform Component
    TransformComponent* pTransform = componentFactory.CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    //Add Render Component
    RenderComponent* pRenderComponent = componentFactory.CreateRenderComponent(pObject, pTransform);
    pObject->AddComponent(k_renderComponentID, pRenderComponent);

    //Add Rigidbody
    Rigidbody* pRigidbody = componentFactory.CreateRigidbodyComponent(pObject, pTransform, k_pCollisionSystem);
    pObject->AddComponent(pRigidbody->GetComponentID(), pRigidbody);

    //Add Character Controller Component
    CharacterController* pCharacterControllerComponent = componentFactory.CreateCharacterControllerComponent(pObject, pTransform, pRigidbody);
    pObject->AddComponent(k_characterControllerComponentID, pCharacterControllerComponent);

    //Add Collider
    Collider* pCollider = componentFactory.CreateCollider(pObject, pTransform, k_pCollisionSystem, pRigidbody);
    PlayerCollisionResponse* pCollisionResponse = new PlayerCollisionResponse(pRigidbody, pCharacterControllerComponent, pRenderComponent);
    pCollider->SetCollisionResponse(pCollisionResponse);
    pObject->AddComponent(pCollider->GetComponentID(), pCollider);



    return pObject;
}

//-------------------------------------------------------------------------------------- -
//  Create Enemy Object
//-------------------------------------------------------------------------------------- -
GameObject* GameObjectFactory::CreateEnemy(Game* pGame, GameObject* pTarget)
{
	GameObjectComponentFactory componentFactory;
	GameObject* pObject = new GameObject(k_enemy_1ID, pGame);

	//Add Transform Component
	TransformComponent* pTransform = componentFactory.CreateTransformComponent(pObject);
	pObject->AddComponent(k_transformComponentID, pTransform);

	//Add Render Component
	RenderComponent* pRenderComponent = componentFactory.CreateRenderComponent(pObject, pTransform);
	pObject->AddComponent(k_renderComponentID, pRenderComponent);

	//Add Rigidbody
    Rigidbody* pRigidbody = componentFactory.CreateRigidbodyComponent(pObject, pTransform, k_pCollisionSystem);
	pObject->AddComponent(pRigidbody->GetComponentID(), pRigidbody);

    //Add Character Controller Component
    CharacterController* pCharacterControllerComponent = componentFactory.CreateCharacterControllerComponent(pObject, pTransform, pRigidbody);
    pObject->AddComponent(k_characterControllerComponentID, pCharacterControllerComponent);

    //Add AI Component
    EnemyAIComponent* pEnemyAIComponent = componentFactory.CreateEnemyAIComponent(pObject, pTransform, pCharacterControllerComponent, pTarget);
    pObject->AddComponent(k_EnemyAIComponentID, pEnemyAIComponent);

    //Add Collider
    Collider* pCollider = componentFactory.CreateCollider(pObject, pTransform, k_pCollisionSystem, pRigidbody);
    pObject->AddComponent(pCollider->GetComponentID(), pCollider);
    EnemyCollisionResponse* pCollisionResponse = new EnemyCollisionResponse(pRigidbody, pEnemyAIComponent);
    pCollider->SetCollisionResponse(pCollisionResponse);

	return pObject;
}