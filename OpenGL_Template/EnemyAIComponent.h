//EnemyAIComponent.h

#ifndef ENEMYAICOMPONENT_H
#define ENEMYAICOMPONENT_H

#include "GameObjectComponent.h"
#include "Vector2.h"

class CharacterController;

class EnemyAIComponent : public GameObjectComponent
{
	GameObject* m_pTarget;
	CharacterController* m_pCharController;

	float m_moveSpeed;
	Vector2_f m_direction;
	Vector2_f m_moveVector;

public:
	EnemyAIComponent(GameObject* pGameObject, TransformComponent* pTransform, CharacterController* pCharController, GameObject* pTarget);
	~EnemyAIComponent();

	virtual void Update() override;

	void SetTarget(GameObject* pTarget) { m_pTarget = pTarget; }

private:
	void FindPlayerDirection();
};

#endif // !ENEMYAICOMPONENT_H