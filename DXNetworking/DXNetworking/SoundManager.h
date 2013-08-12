//#pragma once
//
//#include <fmod.hpp>
//
//#define SoundM SoundManager::Instance()
//
//class SoundManager
//{
//protected:
//	FMOD::System* system;
//	FMOD_RESULT result;
//	unsigned int version;
//	int numDrivers;
//	FMOD_SPEAKERMODE speakerMode;
//	FMOD_CAPS caps;
//	char name[256];
//
//	FMOD::Sound* sound;
//	FMOD::Sound* soundTiger;
//	FMOD::Sound* soundPlane;
//	FMOD::Sound* soundGame;
//	//FMOD_RESULT result;
//	FMOD::Channel* channel;
//	FMOD::Channel* channelTiger;
//	FMOD::Channel* channelPlane;
//	FMOD::Channel* channelGame;
//
//public:
//	SoundManager();
//	~SoundManager(){}
//
//	void PlaySong();
//	void ResumeSong();
//	void PauseSong();
//	void Update();
//
//	void PlayTigerSound();
//	void PlayPlaneSound();
//	void PausePlaneSound();
//
//	void PlayGameSound();
//	void PauseGameSound();
//
//	static SoundManager* Instance()
//	{	static SoundManager instance; return &instance; }
//};