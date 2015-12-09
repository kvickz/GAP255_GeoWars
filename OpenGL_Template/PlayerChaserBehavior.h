//PlayerChaserBehavior.h

#ifndef PLAYERCHASERBEHAVIOR_H
#define PLAYERCHASERBEHAVIOR_H

#include "EnemyBehavior.h"

class PlayerChaserBehavior : public EnemyBehavior
{
private:
    float m_moveSpeed;

public:
    PlayerChaserBehavior(EnemyAIComponent* pAIComponent, float moveSpeed);
    virtual ~PlayerChaserBehavior() override;

    virtual void Execute() override;
};

#endif // !PLAYER
