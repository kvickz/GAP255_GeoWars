//AudioComponent.h

#ifndef AUDIOCOMPONENT_H
#define AUDIOCOMPONENT_H

#include "GameObjectComponent.h"

enum SFX;
class AudioManager;

class AudioComponent : public GameObjectComponent
{
    AudioManager* m_pAudioManager;

public:
    AudioComponent(GameObject* pGameObject, TransformComponent* pTransform, AudioManager* pAudioManager);
    ~AudioComponent();

    void PlaySound(SFX sfxEnum);
};

#endif // !AUDIOCOMPONENT_H