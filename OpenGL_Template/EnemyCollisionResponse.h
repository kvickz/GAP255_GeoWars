//EnemyCollisionResponse.h

#ifndef ENEMYCOLLISIONRESPONSE_H
#define ENEMYCOLLISIONRESPONSE_H

#include "CollisionResponse.h"

class CharacterController;
class EnemyAIComponent;

class EnemyCollisionResponse : public CollisionResponse
{
private:
    EnemyAIComponent* m_pEnemyAIComponent;

public:
    EnemyCollisionResponse(Rigidbody* pRigidbody, EnemyAIComponent* pEnemyAIComponent);

    virtual void Execute(Collision collision);
};

#endif // !ENEMYCOLLISIONRESPONSE_H
