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
CharacterController* GameObjectComponentFactory::CreateCharacterControllerComponent(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody, AudioComponent* pAudioComponent)
{
    CharacterController* pComponent = new CharacterController(pGameObject, pTransform, pRigidbody, pAudioComponent);

    return pComponent;
}

//AI CONTROLLER
EnemyAIComponent* GameObjectComponentFactory::CreateEnemyAIComponent(GameObject* pGameObject, TransformComponent* pTransform, CharacterController* pCharController, GameObject* pTarget, AudioComponent* pAudioComponent, SpawnManager* pSpawnManager)
{
    EnemyAIComponent* pComponent = new EnemyAIComponent(pGameObject, pTransform, pCharController, pTarget, pAudioComponent, pSpawnManager);

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

//PARTICLE
ParticleComponent* GameObjectComponentFactory::CreateParticleComponent(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody)
{
    ParticleComponent* pComponent = new ParticleComponent(pGameObject, pTransform, pRigidbody);

    return pComponent;
}

//GUN COMPONENT
GunComponent* GameObjectComponentFactory::CreateGunComponent(GameObject* pGameObject, TransformComponent* pTransform, SpawnManager* pSpawnManager, AudioComponent* pAudioComponent)
{
    GunComponent* pComponent = new GunComponent(pGameObject, pTransform, pSpawnManager, pAudioComponent);

    return pComponent;
}

//BULLET CONTROLLER
BulletController* GameObjectComponentFactory::CreateBulletController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody, AudioComponent* pAudioComponent)
{
    BulletController* pComponent = new BulletController(pGameObject, pTransform, pRigidbody, pAudioComponent);

    return pComponent;
}

//AUDIO COMPONENT
AudioComponent* GameObjectComponentFactory::CreateAudioComponent(GameObject* pGameObject, TransformComponent* pTransform, AudioManager* pAudioManager)
{
    AudioComponent* pComponent = new AudioComponent(pGameObject, pTransform, pAudioManager);

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