//ShootCommand.cpp

#include "ShootCommand.h"

#include "GameObject.h"
#include "GunComponent.h"

#include "Constants.h"

#include <cmath>

ShootCommand::ShootCommand(GameObject* pGameObject)
    :Command(pGameObject)
{
    m_pGunComponent = pGameObject->GetComponent<GunComponent>(k_gunComponentID);
}

void ShootCommand::Execute()
{
    //TODO: Sometimes velocity is too high for some reason, generally on 90 and 45 degree angles
    float valueX = (float)m_xAxis / (float)k_maxStickInputValue;
    float valueY = (float)m_yAxis / (float)k_maxStickInputValue;

    //Left stick X
    if (m_xAxis < k_deadZoneRange && m_xAxis > -k_deadZoneRange)
        valueX = 0;

    //Y axis, Not sure if it will have a dead zone or how/if it will be handled by controller
    if (m_yAxis < k_deadZoneRange && m_yAxis > -k_deadZoneRange)
        valueY = 0;

    if (valueX == 0 && valueY == 0)
        return;

    //Get Unit Vector
    float xSquared = valueX * valueX;
    float ySquared = valueY * valueY;
    float magnitude = xSquared + ySquared;
    float magnitudeSquared = magnitude * magnitude;

    float xUnit = xSquared / magnitudeSquared;
    float yUnit = ySquared / magnitudeSquared;

    //Account for negative values
    if (valueX < 0)
        xUnit *= -1;

    if (valueY < 0)
        yUnit *= -1;

    //Clamp range -1 to 1
    if (xUnit < -1) xUnit = -1;
    if (xUnit >  1) xUnit =  1;
    if (yUnit < -1) yUnit = -1;
    if (yUnit >  1) yUnit =  1;

    //Plug in
    m_pGunComponent->Shoot(xUnit, -yUnit);
}

void ShootCommand::ResetAxisValues()
{
    m_xAxis = 0;
    m_yAxis = 0;
}