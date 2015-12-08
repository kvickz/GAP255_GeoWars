//GameObjectComponentFactory.h

#ifndef GAMEOBJECTCOMPONENTFACTORY_H
#define GAMEOBJECTCOMPONENTFACTORY_H

//Included here for GameObject Factory
#include "GameObjectComponent.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
#include "CharacterController.h"
#include "Rigidbody.h"
#include "EnemyAIComponent.h"

#include "Constants.h"

class GameObject;
class Renderer;
class Time;

class GameObjectComponentFactory
{
public:
    TransformComponent* CreateTransformComponent(GameObject* pGameObject);
    RenderComponent* CreateRenderComponent(GameObject* pGameObject, TransformComponent* pTransform);
    CameraComponent* CreateCameraComponent(GameObject* pGameObject, TransformComponent* pTransform, Renderer* const pRenderer, Time* const pTime);
    Rigidbody* CreateRigidbodyComponent(GameObject* pGameObject, TransformComponent* pTransform);
    CharacterController* CreateCharacterControllerComponent(GameObject* pGameObject, TransformComponent* pTransform, Rigidbody* pRigidbody);
	EnemyAIComponent* CreateEnemyAIComponent(GameObject* pGameObject, TransformComponent* pTransform, CharacterController* pCharController, GameObject* pTarget);
};

#endif // !GAMEOBJECTCOMPONENTFACTORY_H