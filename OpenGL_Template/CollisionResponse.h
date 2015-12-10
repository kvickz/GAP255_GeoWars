//CollisionResponse.h

#ifndef COLLISIONRESPONSE_H
#define COLLISIONRESPONSE_H

class Rigidbody;

#include "Vector3.h"

class CollisionResponse
{
protected:
    Rigidbody* m_pRigidbody;

public:
    CollisionResponse(Rigidbody* pRigidbody);
    virtual ~CollisionResponse() {};

    virtual void Execute(Vector3 force) = 0;
};

#endif // !COLLISIONRESPONSE_H
