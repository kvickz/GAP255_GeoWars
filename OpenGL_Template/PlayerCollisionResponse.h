//PlayerCollisionResponse.h

#ifndef PLAYERCOLLISIONRESPONSE_H
#define PLAYERCOLLISIONRESPONSE_H

#include "CollisionResponse.h"

class CharacterController;
class RenderComponent;

class PlayerCollisionResponse : public CollisionResponse
{
private:
    CharacterController* m_pCharacterController;
    RenderComponent* m_pRenderComponent;

public:
    PlayerCollisionResponse(Rigidbody* pRigidbody, CharacterController* pCharacterController, RenderComponent* pRenderComponent);

    virtual void Execute(Collision collision);
};

#endif // !PLAYERCOLLISIONRESPONSE_H