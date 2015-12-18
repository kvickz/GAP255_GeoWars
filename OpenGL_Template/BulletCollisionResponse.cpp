//BulletCollisionResponse.cpp

#include "BulletCollisionResponse.h"

#include "Rigidbody.h"
#include "BulletController.h"
#include "GameObject.h"

#include "Collision.h"

#include "Constants.h"

BulletCollisionResponse::BulletCollisionResponse(Rigidbody* pRigidbody, BulletController* pBulletController)
    :CollisionResponse(pRigidbody)
    , m_pBulletController(pBulletController)
{
    //
}

void BulletCollisionResponse::Execute(Collision collision)
{
    if (collision.m_objectID != k_bulletID)
        m_pBulletController->DestroyBullet();
}
