//ShootCommand.h

#ifndef SHOOTCOMMAND_H
#define SHOOTCOMMAND_H

#include "Command.h"

class GunComponent;

class ShootCommand : public Command
{
private:
    GunComponent* m_pGunComponent;

    AxisValue m_xAxis;
    AxisValue m_yAxis;

public:
    ShootCommand(GameObject* pGameObject);

    virtual void Execute() override;
    virtual void SetAxisXValue(AxisValue value) override { m_xAxis = value; }
    virtual void SetAxisYValue(AxisValue value) override { m_yAxis = value; }
    virtual void ResetAxisValues() override;
};

#endif // !SHOOTCOMMAND_H
