//CollisionResponse.h

#ifndef COLLISIONRESPONSE_H
#define COLLISIONRESPONSE_H

class Rigidbody;
struct Collision;

#include "Vector3.h"

class CollisionResponse
{
protected:
    //TODO: Remove dependency on rigidbody
    Rigidbody* m_pRigidbody;

public:
    CollisionResponse(Rigidbody* pRigidbody);
    virtual ~CollisionResponse() {};

    virtual void Execute(Collision collision) = 0;
};

#endif // !COLLISIONRESPONSE_H
