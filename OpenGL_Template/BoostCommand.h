//BoostCommand.h

#ifndef BOOSTCOMMAND_H
#define BOOSTCOMMAND_H

#include "Command.h"

class CharacterController;

class BoostCommand : public Command
{
private:
    CharacterController* pCharController;
    AxisValue m_xAxis;
    AxisValue m_yAxis;

public:
    BoostCommand(GameObject* pGameObject);
    ~BoostCommand();

    virtual void Execute() override;
    /*virtual void SetAxisXValue(AxisValue value) override { m_xAxis = value; }
    virtual void SetAxisYValue(AxisValue value) override { m_yAxis = value; }
    virtual void ResetAxisValues() override;*/
};

#endif // !BOOSTCOMMAND_H
