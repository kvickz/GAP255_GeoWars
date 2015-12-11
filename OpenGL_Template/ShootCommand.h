//ShootCommand.h

#ifndef SHOOTCOMMAND_H
#define SHOOTCOMMAND_H

#include "Command.h"

class GunComponent;

class ShootCommand : public Command
{
private:
    GunComponent* m_pGunComponent;

public:
    ShootCommand(GameObject* pGameObject);
    virtual void Execute() override;
};

#endif // !SHOOTCOMMAND_H
