//GameObjectComponentFactory.h

#ifndef GAMEOBJECTCOMPONENTFACTORY_H
#define GAMEOBJECTCOMPONENTFACTORY_H

//Included here for GameObject Factory
#include "GameObjectComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
#include "ParticleComponent.h"
#include "CharacterStats.h"
#include "CharacterController.h"
#include "EnemyAIComponent.h"
#include "CharacterStats.h"
#include "GunComponent.h"
#include "BulletController.h"
#include "Collider.h"
#include "Rigidbody.h"

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
    CharacterController* CreateCharacterControllerComponent(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody);
	EnemyAIComponent* CreateEnemyAIComponent(GameObject* pGameObject, TransformComponent* pTransform, CharacterController* pCharController, GameObject* pTarget);
    Collider* CreateCollider(GameObject* pGameObject, TransformComponent* pTransform, CollisionSystem* pCollisionSystem, Rigidbody* pRigidbody);
    CharacterStats* CreateCharacterStats(GameObject* pGameObject, TransformComponent* pTransform);
    ParticleComponent* CreateParticleComponent(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody);
    GunComponent* CreateGunComponent(GameObject* pGameObject, TransformComponent* pTransform, SpawnManager* pSpawnManager);
    BulletController* CreateBulletController(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody);

    //Function Template
    //* Create(GameObject* pGameObject, TransformComponent* pTransform);
};

#endif // !GAMEOBJECTCOMPONENTFACTORY_H