//MovePlayerCommand.h

#ifndef MOVEPLAYERCOMMAND_H
#define MOVEPLAYERCOMMAND_H

#include "Command.h"

class CharacterController;
class MovePlayerCommand : public Command
{
private:
    CharacterController* m_pCharacterController;
    AxisValue m_xAxis;
    AxisValue m_yAxis;

public:
    MovePlayerCommand(GameObject* pGameObject);

    virtual void Execute() override;
    virtual void SetAxisXValue(AxisValue value) override { m_xAxis = value; }
    virtual void SetAxisYValue(AxisValue value) override { m_yAxis = value; }
    virtual void ResetAxisValues() override;
};

#endif // !MOVEPLAYERCOMMAND_H