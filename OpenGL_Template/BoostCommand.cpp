//BoostCommand.cpp

#include "BoostCommand.h"

#include "GameObject.h"
#include "CharacterController.h"

BoostCommand::BoostCommand(GameObject* pGameObject)
    :Command(pGameObject)
{
    pCharController = pGameObject->GetComponent<CharacterController>(k_characterControllerComponentID);
}

BoostCommand::~BoostCommand()
{

}

void BoostCommand::Execute()
{
    pCharController->Boost();
}