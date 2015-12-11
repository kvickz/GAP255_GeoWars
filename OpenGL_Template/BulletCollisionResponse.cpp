//BulletCollisionResponse.cpp

#include "BulletCollisionResponse.h"

#include "Rigidbody.h"
#include "GameObject.h"

#include "Collision.h"

BulletCollisionResponse::BulletCollisionResponse(Rigidbody* pRigidbody)
    :CollisionResponse(pRigidbody)
{
    //
}

void BulletCollisionResponse::Execute(Collision collision)
{
    m_pRigidbody->GetGameObject()->DeleteObject();
}
