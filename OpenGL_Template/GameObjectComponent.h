//GameObjectComponent.h

#ifndef GAMEOBJECTCOMPONENT_H
#define GAMEOBJECTCOMPONENT_H

#include "Constants.h"

class GameObject;
class TransformComponent;
class EventSystem;

class GameObjectComponent
{
private:
    bool m_active;
    ComponentID m_componentID;

protected:
    GameObject* m_pGameObject;
    TransformComponent* m_pTransform;

public:
    GameObjectComponent(const ComponentID id, GameObject* pGameObject, TransformComponent* pTransform);
    virtual ~GameObjectComponent() {};

    virtual void Init() {};
    virtual void Update() {};
    virtual void Destroy() {};

    TransformComponent* GetTransform() { return m_pTransform; }
    GameObject* GetGameObject() { return m_pGameObject; }
    const ComponentID GetGameObjectID();
    const ComponentID GetComponentID() { return m_componentID; }
    EventSystem* const GetEventSystem();
};

#endif // !GAMEOBJECTCOMPONENT_H