//EnemyAIComponent.cpp

#include "EnemyAIComponent.h"

#include "CharacterController.h"
#include "TransformComponent.h"
#include "GameObject.h"

#include "Constants.h"

#include <math.h>

EnemyAIComponent::EnemyAIComponent(GameObject* pGameObject, TransformComponent* pTransform, CharacterController* pCharController, GameObject* pTarget)
	:GameObjectComponent(k_EnemyAIComponentID, pGameObject, pTransform)
	, m_pCharController(pCharController)
	, m_pTarget(pTarget)
	, m_moveSpeed(0.5f)
{
	//
}

EnemyAIComponent::~EnemyAIComponent()
{
	//
}

#include <SDL.h>
#include "Time.h"

void EnemyAIComponent::Update()
{
	//Spinning
	//float rotateSpeed = 0.5f;
	//m_pTransform->Rotate(0, rotateSpeed, 0);

	//Scaling
	//float scaleMag = 0.01f;
	//float scaleSpeed = 1.f;
	//scaleMag = sinf(SDL_GetTicks() * scaleSpeed) * scaleMag + scaleMag;
	//m_pTransform->Scale(scaleMag, 0, scaleMag);

	//Moving
	m_pCharController->Move(m_moveVector.x, m_moveVector.y);

	//Find Player Direction
	if (m_pTarget)
	{
		FindPlayerDirection();
	}

	//Update move direction/speed
	m_moveVector.x = m_direction.x * m_moveSpeed;
	m_moveVector.y = m_direction.y * m_moveSpeed;
}

#include "Vector3.h"

void EnemyAIComponent::FindPlayerDirection()
{
	//Get Unit Vector on x and z planes
	Vector3 targetPos = m_pTarget->GetTransformComponent()->GetPosition();
	Vector3 myPos = m_pTransform->GetPosition();

	float xDistance = (targetPos.x - myPos.x);
	float yDistance = -(targetPos.z - myPos.z);

	float xDistSquared = xDistance * xDistance;
	float yDistSquared = yDistance * yDistance;

	float magnitude = xDistSquared + yDistSquared;

	magnitude = sqrt(magnitude);

	m_direction.x = xDistance / magnitude;
	m_direction.y = yDistance / magnitude;
}