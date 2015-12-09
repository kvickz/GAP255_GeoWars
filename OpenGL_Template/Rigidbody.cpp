//Rigidbody.cpp

#include "Rigidbody.h"

#include "TransformComponent.h"
#include "Constants.h"

Rigidbody::Rigidbody(GameObject* pGameObject, TransformComponent* pTransform)
    :GameObjectComponent(k_rigidbodyComponentID, pGameObject, pTransform)
    , m_dragFactor(0.9f)
{
    //
}

void Rigidbody::Update()
{
    //Update Velocity
    m_pTransform->Translate(m_velocity.x, 0, m_velocity.y);

    AddDrag();

	CheckForLevelBarrier();
}

void Rigidbody::AddDrag()
{
    m_velocity.x *= m_dragFactor;
    m_velocity.y *= m_dragFactor;
}

void Rigidbody::AddForce(float x, float y)
{
	//Adding velocity
    m_velocity.x += x;
    m_velocity.y += y;
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
    {
        if (worldPos.x < levelBoundaries->left)
            m_pTransform->SetPosition(levelBoundaries->left, worldPos.y, worldPos.z);

        if (worldPos.x > levelBoundaries->right)
            m_pTransform->SetPosition(levelBoundaries->right, worldPos.y, worldPos.z);

        BounceHorizontal();
    }
		
	
	//Beyond top & bottom
    if (worldPos.z > levelBoundaries->top || worldPos.z < levelBoundaries->bottom)
    {
        if (worldPos.z > levelBoundaries->top)
            m_pTransform->SetPosition(worldPos.x, worldPos.y, levelBoundaries->top);

        if (worldPos.z < levelBoundaries->bottom)
            m_pTransform->SetPosition(worldPos.x, worldPos.y, levelBoundaries->bottom);

        BounceVertical();
    }
		
}

void Rigidbody::BounceHorizontal()
{
	m_velocity.x *= -1.0f;
}

void Rigidbody::BounceVertical()
{
	m_velocity.y *= -1.0f;
}