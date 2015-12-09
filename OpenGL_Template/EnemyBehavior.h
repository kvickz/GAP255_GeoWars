//EnemyBehavior.h

#ifndef ENEMYBEHAVIOR_H
#define ENEMYBEHAVIOR_H

class EnemyAIComponent;

class EnemyBehavior
{
protected:
    EnemyAIComponent* m_pAIComponent;

public:
    EnemyBehavior(EnemyAIComponent* pAIComponent) 
        :m_pAIComponent(pAIComponent)
    {};

    virtual ~EnemyBehavior() {};

    virtual void Execute() = 0;
};

#endif // !ENEMYBEHAVIOR_H
