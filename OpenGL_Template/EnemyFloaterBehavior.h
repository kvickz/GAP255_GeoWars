//EnemyFloaterBehavior.h

#ifndef ENEMYFLOATERBEHAVIOR_H
#define ENEMYFLOATERBEHAVIOR_H

#include "EnemyBehavior.h"

class EnemyFloaterBehavior : public EnemyBehavior
{
private:
    float m_moveSpeed;

public:
    EnemyFloaterBehavior(EnemyAIComponent* pAIComponent, float moveSpeed);
    ~EnemyFloaterBehavior();

    virtual void Execute() override;
};

#endif // !ENEMYFLOATERBEHAVIOR_H
