//CameraMoveCommand.h

#ifndef CAMERAMOVECOMMAND_H
#define CAMERAMOVECOMMAND_H

#include "Command.h"

class CameraComponent;

class CameraMoveCommand : public Command
{
private:
    AxisValue m_xAxis;
    AxisValue m_yAxis;
    AxisValue m_zAxis;

    CameraComponent* const m_pCameraComponent;  //TODO: Figure out case for if component gets deleted

public:
    CameraMoveCommand(GameObject* const pGameObject, CameraComponent* const pCameraComponent);
    ~CameraMoveCommand();

    virtual void Execute() override;
    virtual void SetAxisXValue(AxisValue value) override { m_xAxis = value; }
    virtual void SetAxisYValue(AxisValue value) override { m_yAxis = value; }
    virtual void SetAxisZValue(AxisValue value) override { m_zAxis = value; }
    virtual void ResetAxisValues() override;
};

#endif // !MOVECOMMAND_H
