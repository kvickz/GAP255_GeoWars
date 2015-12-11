//EnemyAIComponent.h

#ifndef ENEMYAICOMPONENT_H
#define ENEMYAICOMPONENT_H

#include "GameObjectComponent.h"
#include "EventListener.h"
#include "Vector2.h"

class CharacterController;
class PlayerChaserBehavior;
class EnemyFloaterBehavior;
class EnemyBehavior;
class Rigidbody;

enum EnemyBehaviorType
{
      k_chaser
    , k_floater
    , k_none
};

class EnemyAIComponent : public GameObjectComponent, public EventListener
{

private:
    friend EnemyBehavior;
    friend PlayerChaserBehavior;
    friend EnemyFloaterBehavior;

    EnemyBehaviorType m_behaviorType;
    EnemyBehavior* m_pBehavior;

	GameObject* m_pTarget;
	CharacterController* m_pCharController;

    //std::pair<float, float> m_possibleSpeeds;
    float rotateSpeed;
	float m_moveSpeed;
    float m_maxSpeed;
	Vector2_f m_direction;
	Vector2_f m_moveVector;

    bool m_chasingPlayer;

public:
	EnemyAIComponent(GameObject* pGameObject, TransformComponent* pTransform, CharacterController* pCharController, GameObject* pTarget);
	~EnemyAIComponent();

	virtual void Update() override;
	void SetTarget(GameObject* pTarget) { m_pTarget = pTarget; }

    void SetBehavior(EnemyBehaviorType type);
    virtual void OnEvent(Event* pEvent) override;

    void Kill();

private:
    void RegisterForEvents();
	void FindPlayerDirection();
};

#endif // !ENEMYAICOMPONENT_H