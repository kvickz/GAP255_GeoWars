//Command.h

#ifndef COMMAND_H
#define COMMAND_H

class GameObject;

typedef int AxisValue;

class Command
{
protected:
    //TODO: Check coding standards for static const
    static const AxisValue k_maxStickInputValue = 0x7fffffff;
    static const AxisValue k_deadZoneRange = 8000;

    GameObject* const m_pGameObject;

public:
    Command(GameObject* const pGameObject);

    virtual void Execute() = 0;
    virtual void SetAxisXValue(AxisValue value) {}
    virtual void SetAxisYValue(AxisValue value) {}
    virtual void SetAxisZValue(AxisValue value) {}
    virtual void ResetAxisValues() {};
};

#endif // !COMMAND_H
