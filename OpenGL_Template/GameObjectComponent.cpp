//GameObjectComponent.cpp

#include "GameObjectComponent.h"
#include "GameObject.h"

GameObjectComponent::GameObjectComponent(const ComponentID id, GameObject* pGameObject, TransformComponent* pTransform)
    :m_componentID(id)
    , m_pGameObject(pGameObject)
    , m_pTransform(pTransform)
{
    //
}

EventSystem* const GameObjectComponent::GetEventSystem()
{
    return m_pGameObject->GetEventSystem();
}

const ComponentID GameObjectComponent::GetGameObjectID()
{
    return m_pGameObject->GetObjectID();
}