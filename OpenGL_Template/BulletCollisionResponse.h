//BulletCollisionResponse.h

#ifndef BULLETCOLLISIONRESPONSE_H
#define BULLETCOLLISIONRESPONSE_H

#include "CollisionResponse.h"

class BulletController;

class BulletCollisionResponse : public CollisionResponse
{ 
private:
    BulletController* m_pBulletController;

public:
    BulletCollisionResponse(Rigidbody* pRigidbody, BulletController* pBulletController);
    virtual void Execute(Collision collision);
};

#endif // !BULLETCOLLISIONRESPONSE_H