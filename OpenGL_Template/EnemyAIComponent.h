//EnemyAIComponent.h

#ifndef ENEMYAICOMPONENT_H
#define ENEMYAICOMPONENT_H

#include "GameObjectComponent.h"
#include "Vector2.h"

class CharacterController;
class PlayerChaserBehavior;
class EnemyFloaterBehavior;
class EnemyBehavior;
class Rigidbody;

class EnemyAIComponent : public GameObjectComponent
{
private:
    friend EnemyBehavior;
    friend PlayerChaserBehavior;
    friend EnemyFloaterBehavior;

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

private:
	void FindPlayerDirection();
    void SetBehavior();
};

#endif // !ENEMYAICOMPONENT_H