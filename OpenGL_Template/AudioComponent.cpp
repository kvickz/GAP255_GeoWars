//AudioComponent.cpp

#include "AudioComponent.h"

#include "AudioFileEnums.h"
#include "AudioManager.h"

AudioComponent::AudioComponent(GameObject* pGameObject, TransformComponent* pTransform, AudioManager* pAudioManager)
    :GameObjectComponent(k_audioComponentID, pGameObject, pTransform)
    , m_pAudioManager(pAudioManager)
{
    //
}

AudioComponent::~AudioComponent()
{
    m_pAudioManager = nullptr;
}

void AudioComponent::PlaySound(SFX sfxEnum)
{
    m_pAudioManager->PlayOneShot(sfxEnum);
}
