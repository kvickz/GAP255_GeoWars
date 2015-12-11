//BulletCollisionResponse.h

#ifndef BULLETCOLLISIONRESPONSE_H
#define BULLETCOLLISIONRESPONSE_H

#include "CollisionResponse.h"

class BulletCollisionResponse : public CollisionResponse
{
public:
    BulletCollisionResponse(Rigidbody* pRigidbody);
    virtual void Execute(Collision collision);
};


#endif // !BULLETCOLLISIONRESPONSE_H
