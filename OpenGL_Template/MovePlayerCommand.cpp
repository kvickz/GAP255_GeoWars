//MovePlayerCommand.cpp

#include "MovePlayerCommand.h"

#include "CharacterController.h"
#include "GameObject.h"
#include "Constants.h"

MovePlayerCommand::MovePlayerCommand(GameObject* pGameObject)
    :Command(pGameObject)
{
    ResetAxisValues();

    m_pCharacterController = pGameObject->GetComponent<CharacterController>(k_characterControllerComponentID);
}

void MovePlayerCommand::Execute()
{
    float valueX = (float)m_xAxis / (float)k_maxStickInputValue;
    float valueY = (float)m_yAxis / (float)k_maxStickInputValue;

    //Left stick X
    if (m_xAxis < k_deadZoneRange && m_xAxis > -k_deadZoneRange)
        valueX = 0;

    //Y axis, Not sure if it will have a dead zone or how/if it will be handled by controller
    if (m_yAxis < k_deadZoneRange && m_yAxis > -k_deadZoneRange)
        valueY = 0;

    //Calling the component
    //m_pCharacterController->SetMovementScaleX(valueX);
    //m_pCharacterController->SetMovementScaleY(valueY);

    if (valueX == 0 && valueY == 0)
        return;

    m_pCharacterController->Move((float)valueX, (float)valueY);
}

void MovePlayerCommand::ResetAxisValues()
{
    m_xAxis = 0;
    m_yAxis = 0;
}