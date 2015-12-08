//Rigidbody.cpp

#include "Rigidbody.h"

#include "TransformComponent.h"
#include "Constants.h"

Rigidbody::Rigidbody(GameObject* pGameObject, TransformComponent* pTransform)
    :GameObjectComponent(k_rigidbodyComponentID, pGameObject, pTransform)
    , m_maxSpeed(1)
{
    //
}

void Rigidbody::Update()
{
    //Update Velocity
    m_pTransform->Translate(m_velocity.x, 0, m_velocity.y);

	ResetVelocity();

	CheckForLevelBarrier();
}

void Rigidbody::ResetVelocity()
{
	m_velocity.x *= 0.9f;
	m_velocity.y *= 0.9f;
}

void Rigidbody::AddForce(float x, float y)
{
	//Adding velocity
    m_velocity.x += x;
    m_velocity.y += y;

	/*
	//Limiting the acceleration speed
    if (m_velocity.x > m_maxSpeed)
        m_velocity.x = m_maxSpeed;

    if (m_velocity.x < -m_maxSpeed)
        m_velocity.x = -m_maxSpeed;

    if (m_velocity.y > m_maxSpeed)
        m_velocity.y = m_maxSpeed;

    if (m_velocity.y < -m_maxSpeed)
        m_velocity.y = -m_maxSpeed;
		*/
}

#include "GameObject.h"
#include "Game.h"

void Rigidbody::CheckForLevelBarrier()
{
	Game* pGame = m_pGameObject->GetGame();
	const Game::LevelBoundary* levelBoundaries = pGame->GetLevelBoundaries();

	Vector3 worldPos = m_pTransform->GetWorldPosition();

	//Beyond left & right
	if (worldPos.x < levelBoundaries->left || worldPos.x > levelBoundaries->right)
		BounceHorizontal();
	
	//Beyond top & bottom
	if (worldPos.z > levelBoundaries->top || worldPos.z < levelBoundaries->bottom)
		BounceVertical();
}

void Rigidbody::BounceHorizontal()
{
	m_velocity.x *= -1.f;
}

void Rigidbody::BounceVertical()
{
	m_velocity.y *= -1.f;
}