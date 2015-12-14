//GameObjectComponentFactory.h

#ifndef GAMEOBJECTCOMPONENTFACTORY_H
#define GAMEOBJECTCOMPONENTFACTORY_H

//Included here for GameObject Factory
#include "GameObjectComponent.h"
#include "CharacterController.h"
#include "TransformComponent.h"
#include "ParticleComponent.h"
#include "EnemyAIComponent.h"
#include "BulletController.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
#include "CharacterStats.h"
#include "CharacterStats.h"
#include "AudioComponent.h"
#include "GunComponent.h"
#include "Rigidbody.h"
#include "Collider.h"

#include "Constants.h"

class SpawnManager;
class CollisionSystem;
class GameObject;
class Renderer;
class Time;

class GameObjectComponentFactory
{
public:
    TransformComponent* CreateTransformComponent(GameObject* pGameObject);
    RenderComponent* CreateRenderComponent(GameObject* pGameObject, TransformComponent* pTransform);
    CameraComponent* CreateCameraComponent(GameObject* pGameObject, TransformComponent* pTransform, Renderer* const pRenderer, Time* const pTime);
    Rigidbody* CreateRigidbodyComponent(GameObject* pGameObject, TransformComponent* pTransform, CollisionSystem* pCollisionSystem);
    CharacterController* CreateCharacterControllerComponent(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody, AudioComponent* pAudioComponent);
    EnemyAIComponent* CreateEnemyAIComponent(GameObject* pGameObject, TransformComponent* pTransform, CharacterController* pCharController, GameObject* pTarget, AudioComponent* pAudioComponent, SpawnManager* pSpawnManager);
    Collider* CreateCollider(GameObject* pGameObject, TransformComponent* pTransform, CollisionSystem* pCollisionSystem, Rigidbody* pRigidbody);
    CharacterStats* CreateCharacterStats(GameObject* pGameObject, TransformComponent* pTransform);
    ParticleComponent* CreateParticleComponent(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody);
    GunComponent* CreateGunComponent(GameObject* pGameObject, TransformComponent* pTransform, SpawnManager* pSpawnManager, AudioComponent* pAudioComponent);
    BulletController* CreateBulletController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody, AudioComponent* pAudioComponent);
    AudioComponent* CreateAudioComponent(GameObject* pGameObject, TransformComponent* pTransform, AudioManager* pAudioManager);

    //Function Template
    //* Create(GameObject* pGameObject, TransformComponent* pTransform);
};

#endif // !GAMEOBJECTCOMPONENTFACTORY_H