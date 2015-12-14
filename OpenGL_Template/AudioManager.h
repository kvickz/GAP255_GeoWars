//AudioManager.h

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "SDL_mixer.h"

#include <unordered_map>

enum SFX;

class AudioManager
{
private:
    std::unordered_map<SFX, Mix_Chunk*> m_audioFiles;

	Mix_Music* m_pMusic;

public:
	AudioManager();
	~AudioManager();

    void PlayOneShot(SFX fileEnum);
	void PlayMusic();

    void StopMusic();

private:
	void LoadAudioFiles();
};

#endif // !AUDIOMANAGER_H
