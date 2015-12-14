//AudioManager.cpp

#include "AudioManager.h"

#include "AudioFileEnums.h"

#include <SDL.h>

AudioManager::AudioManager()
{
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	Mix_AllocateChannels(64);
	//SDL_OpenAudio()

	//Loading audio files
	LoadAudioFiles();

	PlayMusic();
}

AudioManager::~AudioManager()
{
	//Deleting music track
	Mix_FreeMusic(m_pMusic);
	//Deleting audio files
	auto iterator = m_audioFiles.begin();

	while (iterator != m_audioFiles.end())
	{
		Mix_FreeChunk(iterator->second);
		++iterator;
	}

	Mix_CloseAudio();
	Mix_Quit();
}

void AudioManager::PlayMusic()
{
	Mix_PlayMusic(m_pMusic, -1);
}

void AudioManager::LoadAudioFiles()
{
    m_audioFiles.emplace(k_shoot_01_SFX, Mix_LoadWAV("Audio/Shoot_01.wav"));
    //m_audioFiles.emplace(k_playerDeath_SFX, Mix_LoadWAV("Audio/Shoot_01.wav"));
    m_audioFiles.emplace(k_enemyDeath_SFX, Mix_LoadWAV("Audio/EnemyDeath2.wav"));
    m_audioFiles.emplace(k_bulletDeath_SFX, Mix_LoadWAV("Audio/BulletDeath.wav"));

    Mix_Chunk* pChunk = Mix_LoadWAV("Audio/Shoot_01.wav");

	//Music
	m_pMusic = Mix_LoadMUS("Audio/GeoWars.wav");
}

//-------------------------------------------------------------------------------------- -
//Plays an audio file one shot
//		-Use the AudioFile enum in the AudioManager class to pick a file
//-------------------------------------------------------------------------------------- -
void AudioManager::PlayOneShot(SFX fileEnum)
{
    Mix_Chunk* pChunk = m_audioFiles[fileEnum];

	Mix_PlayChannel(-1, m_audioFiles[fileEnum], 0);
}