//GameObjectFactory.cpp

#include "GameObjectFactory.h"

#include "GameObjectComponentFactory.h"

#include "PlayerCollisionResponse.h"
#include "EnemyCollisionResponse.h"
#include "ParticleCollisionResponse.h"
#include "BulletCollisionResponse.h"

GameObjectFactory::GameObjectFactory(Renderer* const pRenderer, Time* const pTime, CollisionSystem* const pCollisionSystem, AssetManager* const pAssetManager, SpawnManager* const pSpawnManager)
    :k_pRenderer(pRenderer)
    , k_pSpawnManager(pSpawnManager)
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

    //Add Gun Component
    GunComponent* pGunComponent = new GunComponent(pObject, pTransform, k_pSpawnManager);
    pObject->AddComponent(pGunComponent->GetComponentID(), pGunComponent);

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
    pObject->AddComponent(k_enemyAIComponentID, pEnemyAIComponent);

    //Add Collider
    Collider* pCollider = componentFactory.CreateCollider(pObject, pTransform, k_pCollisionSystem, pRigidbody);
    EnemyCollisionResponse* pCollisionResponse = new EnemyCollisionResponse(pRigidbody, pEnemyAIComponent);
    pCollider->SetCollisionResponse(pCollisionResponse);
    pObject->AddComponent(pCollider->GetComponentID(), pCollider);

	return pObject;
}

//-------------------------------------------------------------------------------------- -
//  Create Particle Object
//-------------------------------------------------------------------------------------- -
GameObject* GameObjectFactory::CreateParticle(Game* pGame)
{
    GameObjectComponentFactory componentFactory;
    GameObject* pObject = new GameObject(k_particleID, pGame);

    //Add Transform Component
    TransformComponent* pTransform = componentFactory.CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    //Add Render Component
    RenderComponent* pRenderComponent = componentFactory.CreateRenderComponent(pObject, pTransform);
    pObject->AddComponent(k_renderComponentID, pRenderComponent);

    //Add Rigidbody
    Rigidbody* pRigidbody = componentFactory.CreateRigidbodyComponent(pObject, pTransform, k_pCollisionSystem);
    pRigidbody->SetMass(0.6f);
    pObject->AddComponent(pRigidbody->GetComponentID(), pRigidbody);

    //Add Particle Component
    ParticleComponent* pParticleComponent = componentFactory.CreateParticleComponent(pObject, pTransform, pRigidbody);
    pObject->AddComponent(pParticleComponent->GetComponentID(), pParticleComponent);

    //Add Collider
    Collider* pCollider = componentFactory.CreateCollider(pObject, pTransform, k_pCollisionSystem, pRigidbody);
    pObject->AddComponent(pCollider->GetComponentID(), pCollider);
    ParticleCollisionResponse* pCollisionResponse = new ParticleCollisionResponse(pRigidbody, pParticleComponent);
    pCollider->SetCollisionResponse(pCollisionResponse);
    pCollider->SetRadius(0.5f);

    return pObject;
}

//-------------------------------------------------------------------------------------- -
//  Create Bullet Object
//-------------------------------------------------------------------------------------- -
GameObject* GameObjectFactory::CreateBullet(Game* pGame)
{
    GameObjectComponentFactory componentFactory;
    GameObject* pObject = new GameObject(k_bulletID, pGame);

    //Add Transform Component
    TransformComponent* pTransform = componentFactory.CreateTransformComponent(pObject);
    pObject->AddComponent(k_transformComponentID, pTransform);

    //Add Render Component
    RenderComponent* pRenderComponent = componentFactory.CreateRenderComponent(pObject, pTransform);
    pObject->AddComponent(k_renderComponentID, pRenderComponent);

    //Add Rigidbody
    Rigidbody* pRigidbody = componentFactory.CreateRigidbodyComponent(pObject, pTransform, k_pCollisionSystem);
    pRigidbody->SetMass(0.6f);
    pObject->AddComponent(pRigidbody->GetComponentID(), pRigidbody);

    //Add Bullet Controller
    BulletController* pBulletController = componentFactory.CreateBulletController(pObject, pTransform, pRigidbody);
    pObject->AddComponent(pBulletController->GetComponentID(), pBulletController);

    //Add Collider
    Collider* pCollider = componentFactory.CreateCollider(pObject, pTransform, k_pCollisionSystem, pRigidbody);
    pObject->AddComponent(pCollider->GetComponentID(), pCollider);
    BulletCollisionResponse* pCollisionResponse = new BulletCollisionResponse(pRigidbody);
    pCollider->SetCollisionResponse(pCollisionResponse);
    pCollider->SetRadius(1.8f);

    return pObject;
}