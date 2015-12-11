//ShootCommand.cpp

#include "ShootCommand.h"

#include "GameObject.h"
#include "GunComponent.h"

#include "Constants.h"

ShootCommand::ShootCommand(GameObject* pGameObject)
    :Command(pGameObject)
{
    m_pGunComponent = pGameObject->GetComponent<GunComponent>(k_gunComponentID);
}

void ShootCommand::Execute()
{
    m_pGunComponent->Shoot();
}